CREATE USER catering_application WITH password 'catering_application';
-- CREATE DATABASE catering WITH OWNER = catering_application;
GRANT USAGE ON SCHEMA public TO catering_application;
GRANT ALL ON SCHEMA public TO catering_application;