CREATE INDEX idx_sessions_expiration
ON Sessions (Expiration);

SET GLOBAL event_scheduler = ON;

CREATE EVENT DeleteExpiredSessions
ON SCHEDULE EVERY 10 MINUTE
DO
  DELETE FROM Sessions
  WHERE Expiration <= NOW();
