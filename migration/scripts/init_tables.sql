CREATE TABLE IF NOT EXISTS product
(
    id              SERIAL PRIMARY KEY,
    name            TEXT    NOT NULL,
    caloric_content INTEGER NOT NULL,
    weight          INTEGER NOT NULL,
    price           REAL    NOT NULL
);

CREATE TABLE IF NOT EXISTS dish_type
(
    id   SERIAL PRIMARY KEY,
    name TEXT NOT NULL
);

CREATE TABLE IF NOT EXISTS dish
(
    id        SERIAL PRIMARY KEY,
    name      TEXT                             NOT NULL,
    weight    INTEGER                          NOT NULL,
    image_url TEXT                             NOT NULL,
    dish_type_id INTEGER REFERENCES dish_type (id) NOT NULL
    );

CREATE TABLE IF NOT EXISTS dish_to_product
(
    id         SERIAL PRIMARY KEY,
    dish_id    INTEGER REFERENCES dish (id)    NOT NULL,
    product_id INTEGER REFERENCES product (id) NOT NULL
    );

CREATE TABLE IF NOT EXISTS recipe
(
    id                 SERIAL PRIMARY KEY,
    cooking_time       INTEGER                     NOT NULL,
    cooking_technology TEXT                        NOT NULL,
    dish_id            INTEGER REFERENCES dish (id) NOT NULL
    );

CREATE TABLE IF NOT EXISTS passport
(
    id                     SERIAL PRIMARY KEY,
    first_name             TEXT NOT NULL,
    last_name              TEXT NOT NULL,
    middle_name            TEXT NOT NULL,
    series                 TEXT NOT NULL,
    number                 TEXT NOT NULL,
    department_code        TEXT NOT NULL,
    issuing_authority_name TEXT NOT NULL,
    date_of_issue          DATE NOT NULL
);

CREATE TABLE IF NOT EXISTS health_cert
(
    id           SERIAL PRIMARY KEY,
    number       TEXT NOT NULL,
    receipt_date DATE NOT NULL
);

CREATE TABLE IF NOT EXISTS cook
(
    id             SERIAL PRIMARY KEY,
    address        TEXT                               NOT NULL,
    passport_id    INTEGER REFERENCES passport (id)    NOT NULL,
    health_cert_id INTEGER REFERENCES health_cert (id) NOT NULL
    );

CREATE TABLE IF NOT EXISTS dish_cooking
(
    id             SERIAL PRIMARY KEY,
    servings_count INTEGER                     NOT NULL,
    cooking_date   DATE                        NOT NULL,
    cook_id        INTEGER REFERENCES cook (id) NOT NULL,
    dish_id        INTEGER REFERENCES dish (id) NOT NULL
    );
