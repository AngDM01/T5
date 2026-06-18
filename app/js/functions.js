function goToMain() {
  window.location.href = "/cgi/MainPageCGI.cgi"
}

function gotToLogin() {
  window.location.href = "/cgi/loginCGI.cgi"
}

function sendLogin(event) {
  event.preventDefault();

  const form = document.getElementById('loginForm');
  const formData = new FormData(form);

  fetch('/cgi/LoginCGI.cgi', {
    method: 'POST',
    body: formData
  })
  .then(response => response.json())
  .then(data => {
    console.log('Respuesta del servidor:', data);

    if (data.success) {
      createNotify('succ', data.message || 'Inicio de sesión exitoso');

      setTimeout(() => {
        window.location.href = '/cgi/HomeCGI.cgi';
      }, 1000);
    } else {
      createNotify('warn', data.message);
    }
  })
  .catch(error => {
    console.error('Error:', error);
    createNotify('err', error.message);
  });
}

function goToRegister() {
  window.location.href = "/cgi/RegisterCGI.cgi"
}

function sendRegister(event) {
  event.preventDefault();

  const form = document.getElementById('RegisterForm');
  const formData = new FormData(form);

  fetch('/cgi/RegisterCGI.cgi', {
    method: 'POST',
    body: formData
  })
  .then(response => response.json())
  .then(data => {
    console.log('Respuesta del servidor:', data);

    if (data.success) {
      createNotify('succ', data.message || 'Registro de cuenta exitoso');

      setTimeout(() => {
        window.location.href = '/cgi/LoginCGI.cgi';
      }, 3000);
    } else {
      createNotify('warn', data.message);
    }
  })
  .catch(error => {
    console.error('Error:', error);
    createNotify('err', error.message);
  });
}

function goToHome() {
  window.location.href = "/cgi/HomeCGI.cgi"
}

function goToCreateLetter() {
  window.location.href = "/cgi/CreateLetterCGI.cgi"
}

function goToImageMaint() {
  window.location.href = "/cgi/ImagesMaintenance.cgi"
}

let notifyTimer = null;

function createNotify(type, message, timer = 5000) {
  const notify = document.getElementById("notify");
  const notifyMessage = document.getElementById("notify-message");

  notify.classList.remove("succ", "err", "warn", "info");

  notify.classList.add(type);

  notifyMessage.textContent = message;

  notify.hidden = false;

  if (notifyTimer) {
    clearTimeout(notifyTimer);
  }

  notifyTimer = setTimeout(closeNotify, timer);
}

function closeNotify() {
  const notify = document.getElementById("notify");
  const notifyMessage = document.getElementById("notify-message");

  notify.hidden = true;

  notify.classList.remove("succ", "err", "warn", "info");
  notifyMessage.textContent = "";

  if (notifyTimer) {
    clearTimeout(notifyTimer);
    notifyTimer = null;
  }
}

function clearForm(form) {
  document.getElementById(form).reset();

  const fileName = document.getElementById("fileName");
  if (fileName) {
    fileName.textContent = "Ningún archivo seleccionado";
  }
}
