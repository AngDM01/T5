CREATE TRIGGER trg_user_registered
AFTER INSERT ON Users
FOR EACH ROW
BEGIN
  INSERT INTO EventLogs (
    Id_event_type,
    Id_associate_user
  )
  VALUES (
    1,
    NEW.Id_user
  );
END

CREATE TRIGGER trg_session_created
AFTER INSERT ON Sessions
FOR EACH ROW
BEGIN
  DECLARE roleId INT;
  DECLARE eventType INT;

  SELECT Id_assigned_rol
  INTO roleId
  FROM Users
  WHERE Id_user = NEW.Id_associate_user;

  IF roleId = 3 THEN
    SET eventType = 7;
  ELSE
    SET eventType = 2;
  END IF;

  INSERT INTO EventLogs (
    Id_event_type,
    Id_associate_user
  )
  VALUES (
    eventType,
    NEW.Id_associate_user
  );
END

CREATE TRIGGER trg_session_deleted
AFTER DELETE ON Sessions
FOR EACH ROW
BEGIN
    DECLARE roleId INT;
    DECLARE eventType INT;

    SELECT Id_assigned_rol
    INTO roleId
    FROM Users
    WHERE Id_user = OLD.Id_associate_user;

    IF roleId = 3 THEN
      SET eventType = 8;
    ELSE
      SET eventType = 6;
    END IF;

    INSERT INTO EventLogs (
      Id_event_type,
      Id_associate_user
    )
    VALUES (
      eventType,
      OLD.Id_associate_user
    );
END

CREATE TRIGGER trg_image_uploaded
AFTER INSERT ON Images
FOR EACH ROW
BEGIN
  INSERT INTO EventLogs (
    Id_event_type,
    Id_associate_user,
    Id_associate_image
  )
  VALUES (
    3,
    NEW.Id_uploader_user,
    NEW.Id_image
  );
END

CREATE TRIGGER trg_image_deleted
AFTER DELETE ON Images
FOR EACH ROW
BEGIN
  INSERT INTO EventLogs (
    Id_event_type,
    Id_associate_user,
    Id_associate_image
  )
  VALUES (
    4,
    OLD.Id_uploader_user,
    OLD.Id_image
  );
END

CREATE TRIGGER trg_letter_sent
AFTER INSERT ON Letters
FOR EACH ROW
BEGIN
  INSERT INTO EventLogs (
    Id_event_type,
    Id_associate_user,
    Id_associate_image
  )
  VALUES (
    5,
    NEW.Id_owner_user,
    NEW.Id_associate_image
  );
END
