CREATE TABLE IF NOT EXISTS product
(
    id              BIGSERIAL PRIMARY KEY,
    name            TEXT    NOT NULL,
    caloric_content INTEGER NOT NULL,
    weight          INTEGER NOT NULL,
    price           REAL    NOT NULL
);

CREATE TABLE IF NOT EXISTS dish_type
(
    id   BIGSERIAL PRIMARY KEY,
    name TEXT NOT NULL
);

CREATE TABLE IF NOT EXISTS dish
(
    id        BIGSERIAL PRIMARY KEY,
    name      TEXT                             NOT NULL,
    weight    INTEGER                          NOT NULL,
    image_url TEXT                             NOT NULL,
    dish_type BIGINT REFERENCES dish_type (id) NOT NULL
    );

CREATE TABLE IF NOT EXISTS dish_to_product
(
    id         BIGSERIAL PRIMARY KEY,
    dish_id    BIGINT REFERENCES dish (id)    NOT NULL,
    product_id BIGINT REFERENCES product (id) NOT NULL
    );

CREATE TABLE IF NOT EXISTS recipe
(
    id                 BIGSERIAL PRIMARY KEY,
    cooking_time       INTEGER                     NOT NULL,
    cooking_technology TEXT                        NOT NULL,
    dish_id            BIGINT REFERENCES dish (id) NOT NULL
    );

CREATE TABLE IF NOT EXISTS passport
(
    id                     BIGSERIAL PRIMARY KEY,
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
    id           BIGSERIAL PRIMARY KEY,
    number       TEXT NOT NULL,
    receipt_date DATE NOT NULL
);

CREATE TABLE IF NOT EXISTS cook
(
    id             BIGSERIAL PRIMARY KEY,
    address        TEXT                               NOT NULL,
    passport_id    BIGINT REFERENCES passport (id)    NOT NULL,
    health_cert_id BIGINT REFERENCES health_cert (id) NOT NULL
    );

CREATE TABLE IF NOT EXISTS dish_cooking
(
    id             BIGSERIAL PRIMARY KEY,
    servings_count INTEGER                     NOT NULL,
    cooking_date   DATE                        NOT NULL,
    cook_id        BIGINT REFERENCES cook (id) NOT NULL,
    dish_id        BIGINT REFERENCES dish (id) NOT NULL
    );
