USE SITIO_TARJETAS;

CREATE TABLE Rol (
    Id_rol INT AUTO_INCREMENT PRIMARY KEY,
    Description VARCHAR(20) NOT NULL
);

CREATE TABLE Users (
    Id_user INT AUTO_INCREMENT PRIMARY KEY,
    Name VARCHAR(100) NOT NULL,
    Age TINYINT UNSIGNED NOT NULL CHECK(Age > 0 AND age < 150),
    Email VARCHAR(255) NOT NULL UNIQUE,
    Password VARCHAR(255) NOT NULL,
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
        REFERENCES Users(Id_user)
);

CREATE TABLE Images (
    Id_image INT AUTO_INCREMENT PRIMARY KEY,
    Alias VARCHAR(255) NOT NULL,
    Extension ENUM('png', 'jpg', 'jpeg') NOT NULL,
    Image_data MEDIUMBLOB NOT NULL,
    Is_catalog BOOLEAN NOT NULL DEFAULT FALSE,
    Upload_date DATETIME NOT NULL DEFAULT CURRENT_TIMESTAMP,
    Id_uploader_user INT NOT NULL,

    CONSTRAINT fk_image_user
        FOREIGN KEY (Id_uploader_user)
        REFERENCES Users(Id_user)
);

CREATE TABLE Letters (
    Id_letter INT AUTO_INCREMENT PRIMARY KEY,
    Letter_title VARCHAR(100) NOT NULL,
    Sender_name VARCHAR(100) NOT NULL,
    Sender_email VARCHAR(255) NOT NULL,
    Receiver_name VARCHAR(100) NOT NULL,
    Receiver_email VARCHAR(255) NOT NULL,
    Text_letter TEXT NOT NULL,
    Send_date DATETIME NOT NULL DEFAULT CURRENT_TIMESTAMP,
    Id_associate_image INT,
    Id_owner_user INT NOT NULL,
    Id_receiver_user INT NOT NULL,

    CONSTRAINT fk_letter_image
        FOREIGN KEY (Id_associate_image)
        REFERENCES Images(Id_image),

    CONSTRAINT fk_letter_sender_user
        FOREIGN KEY (Id_owner_user)
        REFERENCES Users(Id_user),

    CONSTRAINT fk_letter_receiver_user
        FOREIGN KEY (Id_receiver_user)
        REFERENCES Users(Id_user)
);

CREATE TABLE Event_types (
    Id_event_type INT AUTO_INCREMENT PRIMARY KEY,
    Description VARCHAR(255) NOT NULL
);

CREATE TABLE EventLogs (
    Id_event_log INT AUTO_INCREMENT PRIMARY KEY,
    Extra_info TEXT,
    Logged_date DATETIME NOT NULL DEFAULT CURRENT_TIMESTAMP,
    Id_event_type INT NOT NULL,
    Id_associate_user INT,
    Id_associate_image INT,

    CONSTRAINT fk_eventlog_type
        FOREIGN KEY (Id_event_type)
        REFERENCES Event_types(Id_event_type),

    CONSTRAINT fk_eventlog_user
        FOREIGN KEY (Id_associate_user)
        REFERENCES Users(Id_user),

    CONSTRAINT fk_eventlog_image
        FOREIGN KEY (Id_associate_image)
        REFERENCES Images(Id_image)
);

CREATE TABLE Sessions (
    Id_session UUID PRIMARY KEY DEFAULT UUID(),
    Id_associate_user INT NOT NULL,
    Expiration DATETIME NOT NULL,

    CONSTRAINT fk_associate_user
        FOREIGN KEY (Id_associate_user)
        REFERENCES Users(Id_user)
);
