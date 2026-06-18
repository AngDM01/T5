USE Sitio_Tarjetas;

CREATE TABLE Rol (
    Id_rol INT AUTO_INCREMENT PRIMARY KEY,
    Description VARCHAR(20) NOT NULL
);

CREATE TABLE User (
    Id_user INT AUTO_INCREMENT PRIMARY KEY,
    Email VARCHAR(255) NOT NULL UNIQUE,
    Password VARCHAR(255) NOT NULL,
    Name VARCHAR(100) NOT NULL,
    Age TINYINT NOT NULL CHECK(Age > 0),
    Id_assigned_rol INT NOT NULL,

    CONSTRAINT fk_user_role
        FOREIGN KEY (Id_assigned_rol)
        REFERENCES Rol(Id_rol)
);

CREATE TABLE OTP_admin (
    Id_otp INT AUTO_INCREMENT PRIMARY KEY,
    Secret_otp VARCHAR(255) NOT NULL,
    Is_enabled BOOLEAN NOT NULL DEFAULT FALSE,
    Id_owner_user INT NOT NULL,

    CONSTRAINT fk_otp_user
        FOREIGN KEY (Id_owner_user)
        REFERENCES User(Id_user)
);

CREATE TABLE Image (
    Id_image INT AUTO_INCREMENT PRIMARY KEY,
    Name VARCHAR(255) NOT NULL,
    Type ENUM('png', 'jpg', 'jpeg') NOT NULL,
    Data MEDIUMBLOB NOT NULL,
    Is_catalog BOOLEAN NOT NULL DEFAULT FALSE,
    Upload_date DATETIME NOT NULL DEFAULT CURRENT_TIMESTAMP,
    Id_uploader_user INT NOT NULL,

    CONSTRAINT fk_image_user
        FOREIGN KEY (Id_uploader_user)
        REFERENCES User(Id_user)
);

CREATE TABLE Letter (
    Id_letter INT AUTO_INCREMENT PRIMARY KEY,
    Sender_name VARCHAR(100) NOT NULL,
    Sender_email VARCHAR(255) NOT NULL,
    Receiver_name VARCHAR(100) NOT NULL,
    Receiver_email VARCHAR(255) NOT NULL,
    Text TEXT NOT NULL,
    Send_date DATETIME NOT NULL DEFAULT CURRENT_TIMESTAMP,
    Id_associate_image INT,
    Id_owner_user INT NOT NULL,

    CONSTRAINT fk_letter_image
        FOREIGN KEY (Id_associate_image)
        REFERENCES Image(Id_image),

    CONSTRAINT fk_letter_user
        FOREIGN KEY (Id_owner_user)
        REFERENCES User(Id_user)
);

CREATE TABLE Event_type (
    Id_event_type INT AUTO_INCREMENT PRIMARY KEY,
    Description VARCHAR(255) NOT NULL
);

CREATE TABLE EventLog (
    Id_event_log INT AUTO_INCREMENT PRIMARY KEY,
    Extra_info TEXT,
    Logged_date DATETIME NOT NULL DEFAULT CURRENT_TIMESTAMP,
    Id_event_type INT NOT NULL,
    Id_associate_user INT,
    Id_associate_image INT,

    CONSTRAINT fk_eventlog_type
        FOREIGN KEY (Id_event_type)
        REFERENCES Event_type(Id_event_type),

    CONSTRAINT fk_eventlog_user
        FOREIGN KEY (Id_associate_user)
        REFERENCES User(Id_user),

    CONSTRAINT fk_eventlog_image
        FOREIGN KEY (Id_associate_image)
        REFERENCES Image(Id_image)
);
