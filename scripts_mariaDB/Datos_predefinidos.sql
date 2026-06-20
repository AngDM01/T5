USE SITIO_TARJETAS;

INSERT INTO Rol (Description)
VALUES
    ('Invitado'),
    ('Registrado'),
    ('Administrador');

INSERT INTO Event_types (Description)
VALUES
    ('Registro de cuenta'),
    ('Inicio de sesión'),
    ('Carga de una imagen'),
    ('Eliminación de imagen'),
    ('Envío de tarjeta'),
	('Cierre de sesión'),
	('Inicio de sesión administrativo'),
	('Cierre de sesión administrativo');
