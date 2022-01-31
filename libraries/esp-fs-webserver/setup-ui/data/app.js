const svgLock =  '<svg height="16pt" viewBox="0 0 512 512"><path d="m336 512h-288c-26.453125 0-48-21.523438-48-48v-224c0-26.476562 21.546875-48 48-48h288c26.453125 0 48 21.523438 48 48v224c0 26.476562-21.546875 48-48 48zm-288-288c-8.8125 0-16 7.167969-16 16v224c0 8.832031 7.1875 16 16 16h288c8.8125 0 16-7.167969 16-16v-224c0-8.832031-7.1875-16-16-16zm0 0"/><path d="m304 224c-8.832031 0-16-7.167969-16-16v-80c0-52.929688-43.070312-96-96-96s-96 43.070312-96 96v80c0 8.832031-7.167969 16-16 16s-16-7.167969-16-16v-80c0-70.59375 57.40625-128 128-128s128 57.40625 128 128v80c0 8.832031-7.167969 16-16 16zm0 0"/></svg>'
const svgUnlock = '<svg height="16pt" viewBox="0 0 512 512"><path d="m336 512h-288c-26.453125 0-48-21.523438-48-48v-224c0-26.476562 21.546875-48 48-48h288c26.453125 0 48 21.523438 48 48v224c0 26.476562-21.546875 48-48 48zm-288-288c-8.8125 0-16 7.167969-16 16v224c0 8.832031 7.1875 16 16 16h288c8.8125 0 16-7.167969 16-16v-224c0-8.832031-7.1875-16-16-16zm0 0"/><path d="m80 224c-8.832031 0-16-7.167969-16-16v-80c0-70.59375 57.40625-128 128-128s128 57.40625 128 128c0 8.832031-7.167969 16-16 16s-16-7.167969-16-16c0-52.929688-43.070312-96-96-96s-96 43.070312-96 96v80c0 8.832031-7.167969 16-16 16zm0 0"/></svg>'

var options = {};
var connected = false;


// JQuery-like selector
var $ = function(el) {
	return document.getElementById(el);
};


function showPass() {
  var x = document.getElementById("password");
  if (x.type === "password") {
    x.type = "text";
  } else {
    x.type = "password";
  }
}

/**
* Read some data from database
*/
function getWiFiList() {
 var url = new URL("http://" + `${window.location.hostname}` + "/scan");
  fetch(url)
  .then(response => response.json())
  .then(data => {
    listWifiNetworks(data);
  });
}


function selectWifi(row) {
  $('select-' + row.target.parentNode.id).checked = true;
  $('ssid').value = this.cells[1].innerHTML;
  $('ssid-name').innerHTML = this.cells[1].innerHTML;
  $('password').focus();
}


function listWifiNetworks(elems) {

  const list = document.querySelector('#wifi-list');
  list.innerHTML = "";
  var counter = 0;

	elems.forEach(elem => {
   
    // Create a single row with all columns
    var row = document.createElement('tr');
    var id = 'wifi-' + counter++;
    row.id = id;
    row.addEventListener('click', selectWifi); 
	  row.innerHTML  = `<td><input type="radio" name="select" id="select-${id}"></td>`;
    row.innerHTML += `<td id="ssid-${id}">${elem.ssid}</td>`;
    row.innerHTML += '<td>' + elem.strength + '</td>';
    if (elem.security)
      row.innerHTML += '<td>' + svgLock + '</td>';
    else
      row.innerHTML += '<td>' + svgUnlock + '</td>';
  
    // Add row to list
    list.appendChild(row);
    
  });
  
  $("wifi-table").classList.remove("hidden");
}


function getParameters() {
  var url = new URL("http://" + `${window.location.hostname}` + "/config.json");
  fetch(url)
  .then(response => response.json())
  .then(data => {
    
    Object.keys(data).forEach(function(key){
      if (key === 'logo-name' || key === 'logo-svg') {
        console.log(data[key]);
        $(key).innerHTML = data[key];
        delete data[key];
      }
    });

    options = data;
    listParameters(options);
  });
  
}

function listParameters( params) {
  
  $('parameter-list').innerHTML = '';
  for (var key in params) {
    var html;
    // Fiel name label style
    var lblStyle = `width: calc(0.75rem * ${key.length}); text-align:right; padding:10px;`;
    var inputElem = `<input class="opt-input" id="${key}" type="${typeof(params[key])}"`; 
    
    // Set input property (id, type and value)
    // Check first if is boolean
    if (typeof(params[key]) === "boolean"){
      var chk = "";
      if (params[key] === true) chk = "checked";
      html = `<label for="${key}"><input class="opt-input" type="checkbox" role="switch" id="${key}" ${chk}>${key}</label>`;
    } 
    else {
      if (typeof(params[key]) === "string")
        inputElem += ` value="${params[key]}">`;
      else
        inputElem += ` value=${params[key]}>`;
      html = `<input type="text" style="${lblStyle}" value="${key}:" disabled>${inputElem}`;
    }
  
    var div = document.createElement('div');
    div.className = 'button-row';
    div.innerHTML = html;
    $('parameter-list').appendChild(div);
  }
  
  addInputListener();
  $("params-box").classList.remove("hidden");
}

function addInputListener() {
  // Add event listener to option input box to get update options var
  document.querySelectorAll('.opt-input').forEach(item => {
    item.addEventListener('change', event => {
      
      if(item.type === "text") 
        options[item.id] = item.value;
      
      if(item.type === "number") 
        options[item.id] = parseInt(item.value);
      
      if(item.type === "checkbox") 
        options[item.id] = item.checked;
    });
  });
}


function closeModalMessage() {
  $('modal-message').classList.add('hidden');
}

function saveParameters() {
  console.log(options);
  
  var myblob = new Blob([JSON.stringify(options, null, 2)], {
    type: 'application/json'
  });
  var formData = new FormData();
  formData.append("data", myblob, '/config.json');

  // POST data using the Fetch API
  fetch('/edit', {
    method: 'POST',
    headers: {
                'Access-Control-Allow-Origin': '*',
                'Access-Control-Max-Age': '600',
                'Access-Control-Allow-Methods': 'PUT,POST,GET,OPTIONS',
                'Access-Control-Allow-Headers': '*'
             },
    body: formData
  })
  
  // Handle the server response
  .then(response => response.text())
  .then(text => {
    $('message-body').innerHTML = '<br><b>config.json</b> file saved successfully on flash memory!<br><br>';
    $('modal-message').classList.remove('hidden');
  });
}


function doConnection() {
  
  var httpCode;
  var formData = new FormData();
  formData.append('ssid',  $('ssid').value );
  formData.append('password',  $('password').value);
  formData.append('persistent', $('persistent').checked);
  
  var params = `ssid=${$('ssid').value}&password=${$('password').value}&persistent=${$('persistent').checked}`
  fetch('/connect', {
    method: 'POST',
    redirect: 'follow',
    headers: {
                "Content-Type": "application/x-www-form-urlencoded"
             },
    body: params
  })
  
  .then(function(response){
    httpCode = response.status;
    return response.text();
  })
  .then(function(text) {
    if (httpCode === 302) {
      connected = true;
      $('message-body').innerHTML = '<br>ESP connected to <b>' + $('ssid').value + '</b><br><br>';
      $('modal-message').classList.remove('hidden');
    }
    
    if (httpCode === 500) {
      $('message-body').innerHTML = '<br>Error on connection: <b>' +  text + '</b><br><br>';
      $('modal-message').classList.remove('hidden');
    }
  });
  
}

// Initializes the app.
window.addEventListener('load', getParameters);

$('scan-wifi').addEventListener('click', getWiFiList);

$('save-params').addEventListener('click', saveParameters);

// Enable wifi-connect button only if password inserted
$('connect-wifi').disabled = true;
$('password').addEventListener('input', (event) => {
  if( $('password').value.length  === 0 ) {
    $('connect-wifi').disabled = true;
  }
  else {
    $('connect-wifi').disabled = false;
  }
});



