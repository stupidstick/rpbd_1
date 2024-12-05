--
-- PostgreSQL database dump
--

-- Dumped from database version 17.0 (Debian 17.0-1.pgdg120+1)
-- Dumped by pg_dump version 17.0 (Debian 17.0-1.pgdg120+1)

-- Started on 2024-11-09 04:03:52 UTC

SET statement_timeout = 0;
SET lock_timeout = 0;
SET idle_in_transaction_session_timeout = 0;
SET transaction_timeout = 0;
SET client_encoding = 'UTF8';
SET standard_conforming_strings = on;
SELECT pg_catalog.set_config('search_path', '', false);
SET check_function_bodies = false;
SET xmloption = content;
SET client_min_messages = warning;
SET row_security = off;

SET default_tablespace = '';

SET default_table_access_method = heap;

--
-- TOC entry 232 (class 1259 OID 16470)
-- Name: cook; Type: TABLE; Schema: public; Owner: catering_application
--

CREATE TABLE public.cook (
    id integer NOT NULL,
    address text NOT NULL,
    passport_id integer NOT NULL,
    health_cert_id integer NOT NULL
);


ALTER TABLE public.cook OWNER TO catering_application;

--
-- TOC entry 231 (class 1259 OID 16469)
-- Name: cook_id_seq; Type: SEQUENCE; Schema: public; Owner: catering_application
--

CREATE SEQUENCE public.cook_id_seq
    AS integer
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER SEQUENCE public.cook_id_seq OWNER TO catering_application;

--
-- TOC entry 3454 (class 0 OID 0)
-- Dependencies: 231
-- Name: cook_id_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: catering_application
--

ALTER SEQUENCE public.cook_id_seq OWNED BY public.cook.id;


--
-- TOC entry 222 (class 1259 OID 16407)
-- Name: dish; Type: TABLE; Schema: public; Owner: catering_application
--

CREATE TABLE public.dish (
    id integer NOT NULL,
    name text NOT NULL,
    weight integer NOT NULL,
    image_url text NOT NULL,
    dish_type_id integer NOT NULL
);


ALTER TABLE public.dish OWNER TO catering_application;

--
-- TOC entry 234 (class 1259 OID 16489)
-- Name: dish_cooking; Type: TABLE; Schema: public; Owner: catering_application
--

CREATE TABLE public.dish_cooking (
    id integer NOT NULL,
    servings_count integer NOT NULL,
    cooking_date date NOT NULL,
    cook_id integer NOT NULL,
    dish_id integer NOT NULL
);


ALTER TABLE public.dish_cooking OWNER TO catering_application;

--
-- TOC entry 233 (class 1259 OID 16488)
-- Name: dish_cooking_id_seq; Type: SEQUENCE; Schema: public; Owner: catering_application
--

CREATE SEQUENCE public.dish_cooking_id_seq
    AS integer
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER SEQUENCE public.dish_cooking_id_seq OWNER TO catering_application;

--
-- TOC entry 3455 (class 0 OID 0)
-- Dependencies: 233
-- Name: dish_cooking_id_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: catering_application
--

ALTER SEQUENCE public.dish_cooking_id_seq OWNED BY public.dish_cooking.id;


--
-- TOC entry 221 (class 1259 OID 16406)
-- Name: dish_id_seq; Type: SEQUENCE; Schema: public; Owner: catering_application
--

CREATE SEQUENCE public.dish_id_seq
    AS integer
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER SEQUENCE public.dish_id_seq OWNER TO catering_application;

--
-- TOC entry 3456 (class 0 OID 0)
-- Dependencies: 221
-- Name: dish_id_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: catering_application
--

ALTER SEQUENCE public.dish_id_seq OWNED BY public.dish.id;


--
-- TOC entry 224 (class 1259 OID 16421)
-- Name: dish_to_product; Type: TABLE; Schema: public; Owner: catering_application
--

CREATE TABLE public.dish_to_product (
    id integer NOT NULL,
    dish_id integer NOT NULL,
    product_id integer NOT NULL,
    products_count integer NOT NULL
);


ALTER TABLE public.dish_to_product OWNER TO catering_application;

--
-- TOC entry 223 (class 1259 OID 16420)
-- Name: dish_to_product_id_seq; Type: SEQUENCE; Schema: public; Owner: catering_application
--

CREATE SEQUENCE public.dish_to_product_id_seq
    AS integer
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER SEQUENCE public.dish_to_product_id_seq OWNER TO catering_application;

--
-- TOC entry 3457 (class 0 OID 0)
-- Dependencies: 223
-- Name: dish_to_product_id_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: catering_application
--

ALTER SEQUENCE public.dish_to_product_id_seq OWNED BY public.dish_to_product.id;


--
-- TOC entry 220 (class 1259 OID 16398)
-- Name: dish_type; Type: TABLE; Schema: public; Owner: catering_application
--

CREATE TABLE public.dish_type (
    id integer NOT NULL,
    name text NOT NULL
);


ALTER TABLE public.dish_type OWNER TO catering_application;

--
-- TOC entry 219 (class 1259 OID 16397)
-- Name: dish_type_id_seq; Type: SEQUENCE; Schema: public; Owner: catering_application
--

CREATE SEQUENCE public.dish_type_id_seq
    AS integer
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER SEQUENCE public.dish_type_id_seq OWNER TO catering_application;

--
-- TOC entry 3458 (class 0 OID 0)
-- Dependencies: 219
-- Name: dish_type_id_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: catering_application
--

ALTER SEQUENCE public.dish_type_id_seq OWNED BY public.dish_type.id;


--
-- TOC entry 230 (class 1259 OID 16461)
-- Name: health_cert; Type: TABLE; Schema: public; Owner: catering_application
--

CREATE TABLE public.health_cert (
    id integer NOT NULL,
    number text NOT NULL,
    receipt_date date NOT NULL
);


ALTER TABLE public.health_cert OWNER TO catering_application;

--
-- TOC entry 229 (class 1259 OID 16460)
-- Name: health_cert_id_seq; Type: SEQUENCE; Schema: public; Owner: catering_application
--

CREATE SEQUENCE public.health_cert_id_seq
    AS integer
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER SEQUENCE public.health_cert_id_seq OWNER TO catering_application;

--
-- TOC entry 3459 (class 0 OID 0)
-- Dependencies: 229
-- Name: health_cert_id_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: catering_application
--

ALTER SEQUENCE public.health_cert_id_seq OWNED BY public.health_cert.id;


--
-- TOC entry 228 (class 1259 OID 16452)
-- Name: passport; Type: TABLE; Schema: public; Owner: catering_application
--

CREATE TABLE public.passport (
    id integer NOT NULL,
    first_name text NOT NULL,
    last_name text NOT NULL,
    middle_name text NOT NULL,
    series text NOT NULL,
    number text NOT NULL,
    department_code text NOT NULL,
    issuing_authority_name text NOT NULL,
    date_of_issue date NOT NULL
);


ALTER TABLE public.passport OWNER TO catering_application;

--
-- TOC entry 227 (class 1259 OID 16451)
-- Name: passport_id_seq; Type: SEQUENCE; Schema: public; Owner: catering_application
--

CREATE SEQUENCE public.passport_id_seq
    AS integer
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER SEQUENCE public.passport_id_seq OWNER TO catering_application;

--
-- TOC entry 3460 (class 0 OID 0)
-- Dependencies: 227
-- Name: passport_id_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: catering_application
--

ALTER SEQUENCE public.passport_id_seq OWNED BY public.passport.id;


--
-- TOC entry 218 (class 1259 OID 16389)
-- Name: product; Type: TABLE; Schema: public; Owner: catering_application
--

CREATE TABLE public.product (
    id integer NOT NULL,
    name text NOT NULL,
    caloric_content integer NOT NULL,
    weight integer NOT NULL,
    price real NOT NULL
);


ALTER TABLE public.product OWNER TO catering_application;

--
-- TOC entry 217 (class 1259 OID 16388)
-- Name: product_id_seq; Type: SEQUENCE; Schema: public; Owner: catering_application
--

CREATE SEQUENCE public.product_id_seq
    AS integer
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER SEQUENCE public.product_id_seq OWNER TO catering_application;

--
-- TOC entry 3461 (class 0 OID 0)
-- Dependencies: 217
-- Name: product_id_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: catering_application
--

ALTER SEQUENCE public.product_id_seq OWNED BY public.product.id;


--
-- TOC entry 226 (class 1259 OID 16438)
-- Name: recipe; Type: TABLE; Schema: public; Owner: catering_application
--

CREATE TABLE public.recipe (
    id integer NOT NULL,
    cooking_time integer NOT NULL,
    cooking_technology text NOT NULL,
    dish_id integer NOT NULL
);


ALTER TABLE public.recipe OWNER TO catering_application;

--
-- TOC entry 225 (class 1259 OID 16437)
-- Name: recipe_id_seq; Type: SEQUENCE; Schema: public; Owner: catering_application
--

CREATE SEQUENCE public.recipe_id_seq
    AS integer
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER SEQUENCE public.recipe_id_seq OWNER TO catering_application;

--
-- TOC entry 3462 (class 0 OID 0)
-- Dependencies: 225
-- Name: recipe_id_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: catering_application
--

ALTER SEQUENCE public.recipe_id_seq OWNED BY public.recipe.id;


--
-- TOC entry 3257 (class 2604 OID 16473)
-- Name: cook id; Type: DEFAULT; Schema: public; Owner: catering_application
--

ALTER TABLE ONLY public.cook ALTER COLUMN id SET DEFAULT nextval('public.cook_id_seq'::regclass);


--
-- TOC entry 3252 (class 2604 OID 16410)
-- Name: dish id; Type: DEFAULT; Schema: public; Owner: catering_application
--

ALTER TABLE ONLY public.dish ALTER COLUMN id SET DEFAULT nextval('public.dish_id_seq'::regclass);


--
-- TOC entry 3258 (class 2604 OID 16492)
-- Name: dish_cooking id; Type: DEFAULT; Schema: public; Owner: catering_application
--

ALTER TABLE ONLY public.dish_cooking ALTER COLUMN id SET DEFAULT nextval('public.dish_cooking_id_seq'::regclass);


--
-- TOC entry 3253 (class 2604 OID 16424)
-- Name: dish_to_product id; Type: DEFAULT; Schema: public; Owner: catering_application
--

ALTER TABLE ONLY public.dish_to_product ALTER COLUMN id SET DEFAULT nextval('public.dish_to_product_id_seq'::regclass);


--
-- TOC entry 3251 (class 2604 OID 16401)
-- Name: dish_type id; Type: DEFAULT; Schema: public; Owner: catering_application
--

ALTER TABLE ONLY public.dish_type ALTER COLUMN id SET DEFAULT nextval('public.dish_type_id_seq'::regclass);


--
-- TOC entry 3256 (class 2604 OID 16464)
-- Name: health_cert id; Type: DEFAULT; Schema: public; Owner: catering_application
--

ALTER TABLE ONLY public.health_cert ALTER COLUMN id SET DEFAULT nextval('public.health_cert_id_seq'::regclass);


--
-- TOC entry 3255 (class 2604 OID 16455)
-- Name: passport id; Type: DEFAULT; Schema: public; Owner: catering_application
--

ALTER TABLE ONLY public.passport ALTER COLUMN id SET DEFAULT nextval('public.passport_id_seq'::regclass);


--
-- TOC entry 3250 (class 2604 OID 16392)
-- Name: product id; Type: DEFAULT; Schema: public; Owner: catering_application
--

ALTER TABLE ONLY public.product ALTER COLUMN id SET DEFAULT nextval('public.product_id_seq'::regclass);


--
-- TOC entry 3254 (class 2604 OID 16441)
-- Name: recipe id; Type: DEFAULT; Schema: public; Owner: catering_application
--

ALTER TABLE ONLY public.recipe ALTER COLUMN id SET DEFAULT nextval('public.recipe_id_seq'::regclass);


--
-- TOC entry 3445 (class 0 OID 16470)
-- Dependencies: 232
-- Data for Name: cook; Type: TABLE DATA; Schema: public; Owner: catering_application
--

COPY public.cook (id, address, passport_id, health_cert_id) FROM stdin;
1	Moscow, Tverskaya, 12, apt. 45	1	1
2	Saint Petersburg, Nevsky, 102, apt. 3	2	2
3	Kazan, Bauman, 15, apt. 7	3	3
4	Novosibirsk, Lenina, 89, apt. 22	4	4
5	Yekaterinburg, Vaynra, 56, apt. 11	5	5
\.


--
-- TOC entry 3435 (class 0 OID 16407)
-- Dependencies: 222
-- Data for Name: dish; Type: TABLE DATA; Schema: public; Owner: catering_application
--

COPY public.dish (id, name, weight, image_url, dish_type_id) FROM stdin;
1	Borscht	350	https://example.com/images/borscht.jpg	1
2	Caesar Salad	250	https://example.com/images/caesar_salad.jpg	2
3	Chocolate Cake	200	https://example.com/images/chocolate_cake.jpg	3
4	Spring Rolls	150	https://example.com/images/spring_rolls.jpg	4
5	Grilled Chicken Breast	300	https://example.com/images/grilled_chicken.jpg	5
6	Mashed Potatoes	200	https://example.com/images/mashed_potatoes.jpg	6
7	Beef Stroganoff	400	https://example.com/images/beef_stroganoff.jpg	5
8	Greek Salad	250	https://example.com/images/greek_salad.jpg	2
9	Tiramisu	180	https://example.com/images/tiramisu.jpg	3
10	Fried Fish Fillet	350	https://example.com/images/fried_fish.jpg	5
\.


--
-- TOC entry 3447 (class 0 OID 16489)
-- Dependencies: 234
-- Data for Name: dish_cooking; Type: TABLE DATA; Schema: public; Owner: catering_application
--

COPY public.dish_cooking (id, servings_count, cooking_date, cook_id, dish_id) FROM stdin;
1	10	2024-10-11	1	2
2	15	2024-09-15	2	3
3	21	2024-10-12	4	5
4	54	2024-10-22	5	6
5	65	2024-10-23	3	6
6	4	2024-10-24	1	1
7	20	2024-10-05	2	4
8	76	2024-10-11	5	4
9	45	2024-10-11	3	1
\.


--
-- TOC entry 3437 (class 0 OID 16421)
-- Dependencies: 224
-- Data for Name: dish_to_product; Type: TABLE DATA; Schema: public; Owner: catering_application
--

COPY public.dish_to_product (id, dish_id, product_id) FROM stdin;
1	1	1
2	2	3
3	3	8
4	4	2
5	5	10
6	6	6
7	7	15
8	8	12
9	9	9
10	10	5
11	1	7
12	2	4
13	3	13
14	4	1
15	5	11
16	6	14
17	7	2
18	8	6
19	9	8
20	1	15
21	2	4
22	3	12
23	4	10
24	5	5
25	6	9
26	7	3
27	8	7
28	9	14
29	10	1
30	1	11
31	2	13
\.


--
-- TOC entry 3433 (class 0 OID 16398)
-- Dependencies: 220
-- Data for Name: dish_type; Type: TABLE DATA; Schema: public; Owner: catering_application
--

COPY public.dish_type (id, name) FROM stdin;
1	soup
2	salad
3	dessert
4	appetizer
5	entree
6	side dish
\.


--
-- TOC entry 3443 (class 0 OID 16461)
-- Dependencies: 230
-- Data for Name: health_cert; Type: TABLE DATA; Schema: public; Owner: catering_application
--

COPY public.health_cert (id, number, receipt_date) FROM stdin;
1	12561256	2024-11-10
2	12676512	2023-10-11
3	63363471	2024-02-26
4	85643156	2022-05-20
5	75473346	2023-09-03
\.


--
-- TOC entry 3441 (class 0 OID 16452)
-- Dependencies: 228
-- Data for Name: passport; Type: TABLE DATA; Schema: public; Owner: catering_application
--

COPY public.passport (id, first_name, last_name, middle_name, series, number, department_code, issuing_authority_name, date_of_issue) FROM stdin;
4	Olga	Kuznetsova	Sergeevna	7843	123456	345-678	MVD Krasnodar	2017-06-30
3	Alexey	Ivanov	Mikhailovich	6541	876543	234-567	UFMS	2020-01-15
2	Maria	Sidorova	Vladimirovna	1243	345678	789-012	MVD Moscow	2018-07-22
5	Dmitry	Volkov	Andreevich	1256	543210	456-789	MVD	2016-11-05
1	Ivan	Petrov	Alexandrovich	4512	987654	123-456	MVD	2015-03-10
\.


--
-- TOC entry 3431 (class 0 OID 16389)
-- Dependencies: 218
-- Data for Name: product; Type: TABLE DATA; Schema: public; Owner: catering_application
--

COPY public.product (id, name, caloric_content, weight, price) FROM stdin;
1	Bread	250	500	160.05
2	Butter	717	200	245.41
3	Cheese	402	150	373.45
4	Eggs	155	600	213.4
5	Chicken Breast	165	1000	554.84
6	Beef	250	1000	640.2
7	Rice	130	1000	192.06
8	Pasta	350	500	234.74
9	Tomatoes	18	500	117.37
10	Potatoes	77	1000	106.7
11	Carrots	41	500	74.69
12	Apples	52	1000	170.72
13	Bananas	89	1000	192.06
14	Milk	42	1000	138.71
15	Olive Oil	884	500	480.15
\.


--
-- TOC entry 3439 (class 0 OID 16438)
-- Dependencies: 226
-- Data for Name: recipe; Type: TABLE DATA; Schema: public; Owner: catering_application
--

COPY public.recipe (id, cooking_time, cooking_technology, dish_id) FROM stdin;
1	155	Tuda suda	1
2	200	Varit v vode	2
3	60	Zharit	3
4	20	Zapekat	4
5	125	Peremeshat	5
6	53	Vskipyatit	6
\.


--
-- TOC entry 3463 (class 0 OID 0)
-- Dependencies: 231
-- Name: cook_id_seq; Type: SEQUENCE SET; Schema: public; Owner: catering_application
--

SELECT pg_catalog.setval('public.cook_id_seq', 5, true);


--
-- TOC entry 3464 (class 0 OID 0)
-- Dependencies: 233
-- Name: dish_cooking_id_seq; Type: SEQUENCE SET; Schema: public; Owner: catering_application
--

SELECT pg_catalog.setval('public.dish_cooking_id_seq', 9, true);


--
-- TOC entry 3465 (class 0 OID 0)
-- Dependencies: 221
-- Name: dish_id_seq; Type: SEQUENCE SET; Schema: public; Owner: catering_application
--

SELECT pg_catalog.setval('public.dish_id_seq', 10, true);


--
-- TOC entry 3466 (class 0 OID 0)
-- Dependencies: 223
-- Name: dish_to_product_id_seq; Type: SEQUENCE SET; Schema: public; Owner: catering_application
--

SELECT pg_catalog.setval('public.dish_to_product_id_seq', 31, true);


--
-- TOC entry 3467 (class 0 OID 0)
-- Dependencies: 219
-- Name: dish_type_id_seq; Type: SEQUENCE SET; Schema: public; Owner: catering_application
--

SELECT pg_catalog.setval('public.dish_type_id_seq', 6, true);


--
-- TOC entry 3468 (class 0 OID 0)
-- Dependencies: 229
-- Name: health_cert_id_seq; Type: SEQUENCE SET; Schema: public; Owner: catering_application
--

SELECT pg_catalog.setval('public.health_cert_id_seq', 5, true);


--
-- TOC entry 3469 (class 0 OID 0)
-- Dependencies: 227
-- Name: passport_id_seq; Type: SEQUENCE SET; Schema: public; Owner: catering_application
--

SELECT pg_catalog.setval('public.passport_id_seq', 5, true);


--
-- TOC entry 3470 (class 0 OID 0)
-- Dependencies: 217
-- Name: product_id_seq; Type: SEQUENCE SET; Schema: public; Owner: catering_application
--

SELECT pg_catalog.setval('public.product_id_seq', 15, true);


--
-- TOC entry 3471 (class 0 OID 0)
-- Dependencies: 225
-- Name: recipe_id_seq; Type: SEQUENCE SET; Schema: public; Owner: catering_application
--

SELECT pg_catalog.setval('public.recipe_id_seq', 6, true);


--
-- TOC entry 3274 (class 2606 OID 16477)
-- Name: cook cook_pkey; Type: CONSTRAINT; Schema: public; Owner: catering_application
--

ALTER TABLE ONLY public.cook
    ADD CONSTRAINT cook_pkey PRIMARY KEY (id);


--
-- TOC entry 3276 (class 2606 OID 16494)
-- Name: dish_cooking dish_cooking_pkey; Type: CONSTRAINT; Schema: public; Owner: catering_application
--

ALTER TABLE ONLY public.dish_cooking
    ADD CONSTRAINT dish_cooking_pkey PRIMARY KEY (id);


--
-- TOC entry 3264 (class 2606 OID 16414)
-- Name: dish dish_pkey; Type: CONSTRAINT; Schema: public; Owner: catering_application
--

ALTER TABLE ONLY public.dish
    ADD CONSTRAINT dish_pkey PRIMARY KEY (id);


--
-- TOC entry 3266 (class 2606 OID 16426)
-- Name: dish_to_product dish_to_product_pkey; Type: CONSTRAINT; Schema: public; Owner: catering_application
--

ALTER TABLE ONLY public.dish_to_product
    ADD CONSTRAINT dish_to_product_pkey PRIMARY KEY (id);


--
-- TOC entry 3262 (class 2606 OID 16405)
-- Name: dish_type dish_type_pkey; Type: CONSTRAINT; Schema: public; Owner: catering_application
--

ALTER TABLE ONLY public.dish_type
    ADD CONSTRAINT dish_type_pkey PRIMARY KEY (id);


--
-- TOC entry 3272 (class 2606 OID 16468)
-- Name: health_cert health_cert_pkey; Type: CONSTRAINT; Schema: public; Owner: catering_application
--

ALTER TABLE ONLY public.health_cert
    ADD CONSTRAINT health_cert_pkey PRIMARY KEY (id);


--
-- TOC entry 3270 (class 2606 OID 16459)
-- Name: passport passport_pkey; Type: CONSTRAINT; Schema: public; Owner: catering_application
--

ALTER TABLE ONLY public.passport
    ADD CONSTRAINT passport_pkey PRIMARY KEY (id);


--
-- TOC entry 3260 (class 2606 OID 16396)
-- Name: product product_pkey; Type: CONSTRAINT; Schema: public; Owner: catering_application
--

ALTER TABLE ONLY public.product
    ADD CONSTRAINT product_pkey PRIMARY KEY (id);


--
-- TOC entry 3268 (class 2606 OID 16445)
-- Name: recipe recipe_pkey; Type: CONSTRAINT; Schema: public; Owner: catering_application
--

ALTER TABLE ONLY public.recipe
    ADD CONSTRAINT recipe_pkey PRIMARY KEY (id);


--
-- TOC entry 3281 (class 2606 OID 16483)
-- Name: cook cook_health_cert_id_fkey; Type: FK CONSTRAINT; Schema: public; Owner: catering_application
--

ALTER TABLE ONLY public.cook
    ADD CONSTRAINT cook_health_cert_id_fkey FOREIGN KEY (health_cert_id) REFERENCES public.health_cert(id);


--
-- TOC entry 3282 (class 2606 OID 16478)
-- Name: cook cook_passport_id_fkey; Type: FK CONSTRAINT; Schema: public; Owner: catering_application
--

ALTER TABLE ONLY public.cook
    ADD CONSTRAINT cook_passport_id_fkey FOREIGN KEY (passport_id) REFERENCES public.passport(id);


--
-- TOC entry 3283 (class 2606 OID 16495)
-- Name: dish_cooking dish_cooking_cook_id_fkey; Type: FK CONSTRAINT; Schema: public; Owner: catering_application
--

ALTER TABLE ONLY public.dish_cooking
    ADD CONSTRAINT dish_cooking_cook_id_fkey FOREIGN KEY (cook_id) REFERENCES public.cook(id);


--
-- TOC entry 3284 (class 2606 OID 16500)
-- Name: dish_cooking dish_cooking_dish_id_fkey; Type: FK CONSTRAINT; Schema: public; Owner: catering_application
--

ALTER TABLE ONLY public.dish_cooking
    ADD CONSTRAINT dish_cooking_dish_id_fkey FOREIGN KEY (dish_id) REFERENCES public.dish(id);


--
-- TOC entry 3277 (class 2606 OID 16415)
-- Name: dish dish_dish_type_id_fkey; Type: FK CONSTRAINT; Schema: public; Owner: catering_application
--

ALTER TABLE ONLY public.dish
    ADD CONSTRAINT dish_dish_type_id_fkey FOREIGN KEY (dish_type_id) REFERENCES public.dish_type(id);


--
-- TOC entry 3278 (class 2606 OID 16427)
-- Name: dish_to_product dish_to_product_dish_id_fkey; Type: FK CONSTRAINT; Schema: public; Owner: catering_application
--

ALTER TABLE ONLY public.dish_to_product
    ADD CONSTRAINT dish_to_product_dish_id_fkey FOREIGN KEY (dish_id) REFERENCES public.dish(id);


--
-- TOC entry 3279 (class 2606 OID 16432)
-- Name: dish_to_product dish_to_product_product_id_fkey; Type: FK CONSTRAINT; Schema: public; Owner: catering_application
--

ALTER TABLE ONLY public.dish_to_product
    ADD CONSTRAINT dish_to_product_product_id_fkey FOREIGN KEY (product_id) REFERENCES public.product(id);


--
-- TOC entry 3280 (class 2606 OID 16446)
-- Name: recipe recipe_dish_id_fkey; Type: FK CONSTRAINT; Schema: public; Owner: catering_application
--

ALTER TABLE ONLY public.recipe
    ADD CONSTRAINT recipe_dish_id_fkey FOREIGN KEY (dish_id) REFERENCES public.dish(id);


--
-- TOC entry 3453 (class 0 OID 0)
-- Dependencies: 5
-- Name: SCHEMA public; Type: ACL; Schema: -; Owner: pg_database_owner
--

GRANT ALL ON SCHEMA public TO catering_application;


-- Completed on 2024-11-09 04:03:52 UTC

--
-- PostgreSQL database dump complete
--

