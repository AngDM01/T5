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

async function loadLetterTable(isSendedLetters, offset) {
  const params = new URLSearchParams();
  params.append("isSendedLetters", isSendedLetters);
  params.append("offset", offset);

  try {
    const response = await fetch(`/cgi/LetterTablesCGI.cgi?${params}`);

    if (!response.ok) {
      createNotify('err', "Error al cargar la tabla");
    }
    
    const result = await response.json();
    
    if (result.success) {
      const table = result.content;

      document.getElementById("lettersSection").innerHTML = table;
    } else {
      createNotify(result.type, result.message);
    }
  } catch (err) {
    createNotify('err', "Hubo un error al cargar la tabla, no se puedo comunicar con el servidor");
  }
}

function viewLetterDetails(letterId) {
  window.location.href = `/cgi/ViewLetterCGI.cgi?letterId=${letterId}`;
}

function goToCreateLetter() {
  window.location.href = "/cgi/CreateLetterCGI.cgi"
}

function goToImageMaint() {
  window.location.href = "/cgi/ImagesMaintenanceCGI.cgi"
}

async function uploadImage(event) {
  event.preventDefault();

  const form = document.getElementById("imageForm");
  const alias = document.getElementById("alias").value;
  const fileInput = document.getElementById("imageFile");

  console.log(alias);
  
  if (!fileInput.isDefaultNamespace.length) {
    createNotify('info', "Selecciona una imagen");
    return;
  }
 
  const file = fileInput.files[0];
  
  const validation = validateImageFile(file);

  if (!validation) {
    createNotify('warn', "Formato de archivo no valido, solo: jpg, jpeg, png.");
    return;
  }

  const formData = new FormData();
  formData.append("alias", alias);
  formData.append("image", file);

  try {
    const response = await fetch("/cgi/ImagesMaintenanceCGI.cgi", {
      method: "POST",
      body: formData
    });

    if (!response.ok) {
      createNotify('err', "Error al subir la imagen");
    }

    const result = await response.json();

    if (result.success) {
      createNotify('succ', result.message || 'Imagen subida correctamente');

      setTimeout(() => {
        window.location.reload();
      }, 3000);
    } else {
      createNotify('warn', result.message);
    }

  } catch (err) {
    createNotify('err', "Hubo un error al subir la imagen");
  }
}

function deleteImagePopUp(imageId) {
  showModal({
    message: "¿Deseas eliminar esta imagen?",
    confirmText: "Sí, eliminar",
    cancelText: "No",
    onConfirm: async () => {
      await deleteImage(imageId);
    },
    onCancel: () => {
      hideModal();
    }
  });
}

let isDeleting = false;

async function deleteImage(imageId) {
  if (isDeleting) return;
  isDeleting = true;

  try {
    const response = await fetch("/cgi/ImagesMaintenanceCGI.cgi", {
      method: "POST",
      headers: {"Content-Type": "application/json"},
      body: JSON.stringify({ imageId })
    });

    if (!response.ok) {
      createNotify('err', "Error al eliminar la imagen");
    }

    const result = await response.json();

    if (result.success) {
      createNotify('succ', result.message || 'Imagen eliminada correctamente');

      setTimeout(() => {
        window.location.reload();
      }, 2000);
    } else {
      createNotify('warn', result.message);
    }

  } catch (err) {
    createNotify('err', "Hubo un error al eliminar la imagen");
  } finally {
    isDeleting = false;
  }
}

async function loadImages(idContainer, offset, isCatalog = false) {
  try {
    const params = new URLSearchParams();
    params.append("idContainer", idContainer);
    params.append("offset", offset);
    params.append("isCatalog", isCatalog);

    const response = await fetch(`/cgi/ImagesGalleryCGI.cgi?${params}`);

    if (!response.ok) {
      createNotify('err', "Error al mover la galeria");
    }

    const result = await response.json();

    if (result.success) {
      const carruselContainer = document.getElementById(idContainer);

      carruselContainer.innerHTML = result.message;
    } else {
      createNotify(result.type, result.message);
    }
  } catch (err) {
    createNotify('err', "Hubo un error al eliminar la imagen");
  }
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

function validateImageFile(file) {
  if (!file) return false;

  // Extensiones permitidas
  const allowedExtensions = ["png", "jpg", "jpeg"];

  const fileName = file.name.toLowerCase();
  const extension = fileName.split(".").pop();

  if (!allowedExtensions.includes(extension)) return false;

  const allowedMimeTypes = ["image/png", "image/jpeg"];

  if (!allowedMimeTypes.includes(file.type)) {
    return false;
  }

  return true;
}

function showModal({message = "¿Estás seguro?", confirmText = "Aceptar", cancelText = "Cancelar",
    onConfirm = () => {}, onCancel = () => {}}) {
  const modal = document.getElementById("customModal");
  const msg = document.getElementById("modalMessage");
  const btnConfirm = document.getElementById("modalBtnConfirm");
  const btnCancel = document.getElementById("modalBtnCancel");

  msg.textContent = message;
  btnConfirm.textContent = confirmText;
  btnCancel.textContent = cancelText;

  modal.classList.remove("hidden");

  btnConfirm.onclick = () => {
    hideModal();
    onConfirm();
  };

  btnCancel.onclick = () => {
    hideModal();
    onCancel();
  };
}

function hideModal() {
  document.getElementById("customModal").classList.add("hidden");
}

function setBackgroundImage(src) {
  const bg = document.getElementById("bg-img");

  bg.style.backgroundImage = `url('${src}')`;
  bg.style.backgroundSize = "cover";
  bg.style.backgroundPosition = "center";
  bg.style.backgroundRepeat = "no-repeat";
}