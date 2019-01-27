--
-- PostgreSQL database dump
--

-- Dumped from database version 10.6
-- Dumped by pg_dump version 10.6

SET statement_timeout = 0;
SET lock_timeout = 0;
SET idle_in_transaction_session_timeout = 0;
SET client_encoding = 'UTF8';
SET standard_conforming_strings = on;
SELECT pg_catalog.set_config('search_path', '', false);
SET check_function_bodies = false;
SET client_min_messages = warning;
SET row_security = off;

--
-- Name: plpgsql; Type: EXTENSION; Schema: -; Owner: 
--

CREATE EXTENSION IF NOT EXISTS plpgsql WITH SCHEMA pg_catalog;


--
-- Name: EXTENSION plpgsql; Type: COMMENT; Schema: -; Owner: 
--

COMMENT ON EXTENSION plpgsql IS 'PL/pgSQL procedural language';


SET default_tablespace = '';

SET default_with_oids = false;

--
-- Name: estado; Type: TABLE; Schema: public; Owner: usuario
--

CREATE TABLE public.estado (
    id_estado integer NOT NULL,
    nombre_estado character varying NOT NULL
);


ALTER TABLE public.estado OWNER TO usuario;

--
-- Name: estado_id_estado_seq; Type: SEQUENCE; Schema: public; Owner: usuario
--

CREATE SEQUENCE public.estado_id_estado_seq
    AS integer
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER TABLE public.estado_id_estado_seq OWNER TO usuario;

--
-- Name: estado_id_estado_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: usuario
--

ALTER SEQUENCE public.estado_id_estado_seq OWNED BY public.estado.id_estado;


--
-- Name: marcas_telefono; Type: TABLE; Schema: public; Owner: usuario
--

CREATE TABLE public.marcas_telefono (
    id_marca_telefono integer NOT NULL,
    nombre_marca_telefono character varying(25) NOT NULL
);


ALTER TABLE public.marcas_telefono OWNER TO usuario;

--
-- Name: marcas_telefono_id_marca_telefono_seq; Type: SEQUENCE; Schema: public; Owner: usuario
--

CREATE SEQUENCE public.marcas_telefono_id_marca_telefono_seq
    AS integer
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER TABLE public.marcas_telefono_id_marca_telefono_seq OWNER TO usuario;

--
-- Name: marcas_telefono_id_marca_telefono_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: usuario
--

ALTER SEQUENCE public.marcas_telefono_id_marca_telefono_seq OWNED BY public.marcas_telefono.id_marca_telefono;


--
-- Name: modelo_reparacion; Type: TABLE; Schema: public; Owner: usuario
--

CREATE TABLE public.modelo_reparacion (
    id_modelo_telefono integer NOT NULL,
    id_reparacion integer NOT NULL,
    tiempo_modelo_reparacion integer NOT NULL,
    coste_modelo_reparacion numeric NOT NULL,
    id_modelo_reparacion integer NOT NULL
);


ALTER TABLE public.modelo_reparacion OWNER TO usuario;

--
-- Name: modelo_reparacion_id_modelo_reparacion_seq; Type: SEQUENCE; Schema: public; Owner: usuario
--

CREATE SEQUENCE public.modelo_reparacion_id_modelo_reparacion_seq
    AS integer
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER TABLE public.modelo_reparacion_id_modelo_reparacion_seq OWNER TO usuario;

--
-- Name: modelo_reparacion_id_modelo_reparacion_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: usuario
--

ALTER SEQUENCE public.modelo_reparacion_id_modelo_reparacion_seq OWNED BY public.modelo_reparacion.id_modelo_reparacion;


--
-- Name: modelo_reparacion_id_modelo_telefono_seq; Type: SEQUENCE; Schema: public; Owner: usuario
--

CREATE SEQUENCE public.modelo_reparacion_id_modelo_telefono_seq
    AS integer
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER TABLE public.modelo_reparacion_id_modelo_telefono_seq OWNER TO usuario;

--
-- Name: modelo_reparacion_id_modelo_telefono_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: usuario
--

ALTER SEQUENCE public.modelo_reparacion_id_modelo_telefono_seq OWNED BY public.modelo_reparacion.id_modelo_telefono;


--
-- Name: modelo_reparacion_id_reparacion_seq; Type: SEQUENCE; Schema: public; Owner: usuario
--

CREATE SEQUENCE public.modelo_reparacion_id_reparacion_seq
    AS integer
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER TABLE public.modelo_reparacion_id_reparacion_seq OWNER TO usuario;

--
-- Name: modelo_reparacion_id_reparacion_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: usuario
--

ALTER SEQUENCE public.modelo_reparacion_id_reparacion_seq OWNED BY public.modelo_reparacion.id_reparacion;


--
-- Name: modelo_telefono; Type: TABLE; Schema: public; Owner: usuario
--

CREATE TABLE public.modelo_telefono (
    id_modelo_telefono integer NOT NULL,
    id_marca_modelo_telefono integer NOT NULL,
    nombre_modelo_telefono character varying(25) NOT NULL
);


ALTER TABLE public.modelo_telefono OWNER TO usuario;

--
-- Name: modelo_telefono_id_modelo_telefono_seq; Type: SEQUENCE; Schema: public; Owner: usuario
--

CREATE SEQUENCE public.modelo_telefono_id_modelo_telefono_seq
    AS integer
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER TABLE public.modelo_telefono_id_modelo_telefono_seq OWNER TO usuario;

--
-- Name: modelo_telefono_id_modelo_telefono_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: usuario
--

ALTER SEQUENCE public.modelo_telefono_id_modelo_telefono_seq OWNED BY public.modelo_telefono.id_modelo_telefono;


--
-- Name: modelo_telefono_marca_modelo_telefono_seq; Type: SEQUENCE; Schema: public; Owner: usuario
--

CREATE SEQUENCE public.modelo_telefono_marca_modelo_telefono_seq
    AS integer
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER TABLE public.modelo_telefono_marca_modelo_telefono_seq OWNER TO usuario;

--
-- Name: modelo_telefono_marca_modelo_telefono_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: usuario
--

ALTER SEQUENCE public.modelo_telefono_marca_modelo_telefono_seq OWNED BY public.modelo_telefono.id_marca_modelo_telefono;


--
-- Name: orden_detalles; Type: TABLE; Schema: public; Owner: usuario
--

CREATE TABLE public.orden_detalles (
    id_orden integer NOT NULL,
    id_reparacion_modelo integer NOT NULL
);


ALTER TABLE public.orden_detalles OWNER TO usuario;

--
-- Name: orden_detalles_id_orden_seq; Type: SEQUENCE; Schema: public; Owner: usuario
--

CREATE SEQUENCE public.orden_detalles_id_orden_seq
    AS integer
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER TABLE public.orden_detalles_id_orden_seq OWNER TO usuario;

--
-- Name: orden_detalles_id_orden_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: usuario
--

ALTER SEQUENCE public.orden_detalles_id_orden_seq OWNED BY public.orden_detalles.id_orden;


--
-- Name: orden_detalles_id_reparacion_modelo_seq; Type: SEQUENCE; Schema: public; Owner: usuario
--

CREATE SEQUENCE public.orden_detalles_id_reparacion_modelo_seq
    AS integer
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER TABLE public.orden_detalles_id_reparacion_modelo_seq OWNER TO usuario;

--
-- Name: orden_detalles_id_reparacion_modelo_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: usuario
--

ALTER SEQUENCE public.orden_detalles_id_reparacion_modelo_seq OWNED BY public.orden_detalles.id_reparacion_modelo;


--
-- Name: ordenes; Type: TABLE; Schema: public; Owner: usuario
--

CREATE TABLE public.ordenes (
    id_orden integer NOT NULL,
    id_modelo_telefono integer NOT NULL,
    id_tienda integer NOT NULL,
    fecha date DEFAULT now() NOT NULL,
    id_estado integer DEFAULT 1 NOT NULL,
    id_tecnico integer DEFAULT 1 NOT NULL
);


ALTER TABLE public.ordenes OWNER TO usuario;

--
-- Name: ordenes_estado_seq; Type: SEQUENCE; Schema: public; Owner: usuario
--

CREATE SEQUENCE public.ordenes_estado_seq
    AS integer
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER TABLE public.ordenes_estado_seq OWNER TO usuario;

--
-- Name: ordenes_estado_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: usuario
--

ALTER SEQUENCE public.ordenes_estado_seq OWNED BY public.ordenes.id_estado;


--
-- Name: ordenes_id_modelo_telefono_seq; Type: SEQUENCE; Schema: public; Owner: usuario
--

CREATE SEQUENCE public.ordenes_id_modelo_telefono_seq
    AS integer
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER TABLE public.ordenes_id_modelo_telefono_seq OWNER TO usuario;

--
-- Name: ordenes_id_modelo_telefono_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: usuario
--

ALTER SEQUENCE public.ordenes_id_modelo_telefono_seq OWNED BY public.ordenes.id_modelo_telefono;


--
-- Name: ordenes_id_orden_seq; Type: SEQUENCE; Schema: public; Owner: usuario
--

CREATE SEQUENCE public.ordenes_id_orden_seq
    AS integer
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER TABLE public.ordenes_id_orden_seq OWNER TO usuario;

--
-- Name: ordenes_id_orden_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: usuario
--

ALTER SEQUENCE public.ordenes_id_orden_seq OWNED BY public.ordenes.id_orden;


--
-- Name: ordenes_id_tecnico_seq; Type: SEQUENCE; Schema: public; Owner: usuario
--

CREATE SEQUENCE public.ordenes_id_tecnico_seq
    AS integer
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER TABLE public.ordenes_id_tecnico_seq OWNER TO usuario;

--
-- Name: ordenes_id_tecnico_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: usuario
--

ALTER SEQUENCE public.ordenes_id_tecnico_seq OWNED BY public.ordenes.id_tecnico;


--
-- Name: ordenes_id_tienda_seq; Type: SEQUENCE; Schema: public; Owner: usuario
--

CREATE SEQUENCE public.ordenes_id_tienda_seq
    AS integer
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER TABLE public.ordenes_id_tienda_seq OWNER TO usuario;

--
-- Name: ordenes_id_tienda_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: usuario
--

ALTER SEQUENCE public.ordenes_id_tienda_seq OWNED BY public.ordenes.id_tienda;


--
-- Name: reparaciones; Type: TABLE; Schema: public; Owner: usuario
--

CREATE TABLE public.reparaciones (
    id_reparacion integer NOT NULL,
    nombre_reparacion text NOT NULL
);


ALTER TABLE public.reparaciones OWNER TO usuario;

--
-- Name: reparaciones_id_reparacion_seq; Type: SEQUENCE; Schema: public; Owner: usuario
--

CREATE SEQUENCE public.reparaciones_id_reparacion_seq
    AS integer
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER TABLE public.reparaciones_id_reparacion_seq OWNER TO usuario;

--
-- Name: reparaciones_id_reparacion_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: usuario
--

ALTER SEQUENCE public.reparaciones_id_reparacion_seq OWNED BY public.reparaciones.id_reparacion;


--
-- Name: tecnicos; Type: TABLE; Schema: public; Owner: usuario
--

CREATE TABLE public.tecnicos (
    id_tecnico integer NOT NULL,
    nombre_tecnico text NOT NULL
);


ALTER TABLE public.tecnicos OWNER TO usuario;

--
-- Name: tecnicos_id_tecnico_seq; Type: SEQUENCE; Schema: public; Owner: usuario
--

CREATE SEQUENCE public.tecnicos_id_tecnico_seq
    AS integer
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER TABLE public.tecnicos_id_tecnico_seq OWNER TO usuario;

--
-- Name: tecnicos_id_tecnico_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: usuario
--

ALTER SEQUENCE public.tecnicos_id_tecnico_seq OWNED BY public.tecnicos.id_tecnico;


--
-- Name: tiendas; Type: TABLE; Schema: public; Owner: usuario
--

CREATE TABLE public.tiendas (
    id_tienda integer NOT NULL,
    direccion_tienda text NOT NULL,
    ciudad_tienda text NOT NULL,
    pais_tienda text NOT NULL,
    nombre_tienda character varying NOT NULL
);


ALTER TABLE public.tiendas OWNER TO usuario;

--
-- Name: tiendas_id_tienda_seq; Type: SEQUENCE; Schema: public; Owner: usuario
--

CREATE SEQUENCE public.tiendas_id_tienda_seq
    AS integer
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER TABLE public.tiendas_id_tienda_seq OWNER TO usuario;

--
-- Name: tiendas_id_tienda_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: usuario
--

ALTER SEQUENCE public.tiendas_id_tienda_seq OWNED BY public.tiendas.id_tienda;


--
-- Name: estado id_estado; Type: DEFAULT; Schema: public; Owner: usuario
--

ALTER TABLE ONLY public.estado ALTER COLUMN id_estado SET DEFAULT nextval('public.estado_id_estado_seq'::regclass);


--
-- Name: marcas_telefono id_marca_telefono; Type: DEFAULT; Schema: public; Owner: usuario
--

ALTER TABLE ONLY public.marcas_telefono ALTER COLUMN id_marca_telefono SET DEFAULT nextval('public.marcas_telefono_id_marca_telefono_seq'::regclass);


--
-- Name: modelo_reparacion id_modelo_reparacion; Type: DEFAULT; Schema: public; Owner: usuario
--

ALTER TABLE ONLY public.modelo_reparacion ALTER COLUMN id_modelo_reparacion SET DEFAULT nextval('public.modelo_reparacion_id_modelo_reparacion_seq'::regclass);


--
-- Name: modelo_telefono id_modelo_telefono; Type: DEFAULT; Schema: public; Owner: usuario
--

ALTER TABLE ONLY public.modelo_telefono ALTER COLUMN id_modelo_telefono SET DEFAULT nextval('public.modelo_telefono_id_modelo_telefono_seq'::regclass);


--
-- Name: ordenes id_orden; Type: DEFAULT; Schema: public; Owner: usuario
--

ALTER TABLE ONLY public.ordenes ALTER COLUMN id_orden SET DEFAULT nextval('public.ordenes_id_orden_seq'::regclass);


--
-- Name: reparaciones id_reparacion; Type: DEFAULT; Schema: public; Owner: usuario
--

ALTER TABLE ONLY public.reparaciones ALTER COLUMN id_reparacion SET DEFAULT nextval('public.reparaciones_id_reparacion_seq'::regclass);


--
-- Name: tecnicos id_tecnico; Type: DEFAULT; Schema: public; Owner: usuario
--

ALTER TABLE ONLY public.tecnicos ALTER COLUMN id_tecnico SET DEFAULT nextval('public.tecnicos_id_tecnico_seq'::regclass);


--
-- Name: tiendas id_tienda; Type: DEFAULT; Schema: public; Owner: usuario
--

ALTER TABLE ONLY public.tiendas ALTER COLUMN id_tienda SET DEFAULT nextval('public.tiendas_id_tienda_seq'::regclass);


--
-- Data for Name: estado; Type: TABLE DATA; Schema: public; Owner: usuario
--

COPY public.estado (id_estado, nombre_estado) FROM stdin;
1	TRANSPORTE A INSTALACIONES
2	REPARANDO
3	TRANSPORTE A LA TIENDA
\.


--
-- Data for Name: marcas_telefono; Type: TABLE DATA; Schema: public; Owner: usuario
--

COPY public.marcas_telefono (id_marca_telefono, nombre_marca_telefono) FROM stdin;
1	Samsung
2	Huawei
3	Apple
4	Nokia
5	LG
6	Sony
7	HTC
8	BlackBerry
\.


--
-- Data for Name: modelo_reparacion; Type: TABLE DATA; Schema: public; Owner: usuario
--

COPY public.modelo_reparacion (id_modelo_telefono, id_reparacion, tiempo_modelo_reparacion, coste_modelo_reparacion, id_modelo_reparacion) FROM stdin;
1	1	100	12.50	1
1	4	40	23.56	2
2	1	35	60.00	3
2	6	10	70.00	4
3	1	200	45.00	5
3	3	45	76.56	6
4	1	75	2.50	7
5	5	50	43	8
10	1	50	20.00	9
14	3	300	190.00	10
27	3	45	100.00	11
\.


--
-- Data for Name: modelo_telefono; Type: TABLE DATA; Schema: public; Owner: usuario
--

COPY public.modelo_telefono (id_modelo_telefono, id_marca_modelo_telefono, nombre_modelo_telefono) FROM stdin;
1	1	Galaxy A8s
2	1	Galaxy J4 Core
3	1	Galaxy A9 2018
4	1	Galaxy A7
5	1	Galaxy C9 Pro
6	2	Y7 Pro
7	2	Y5 Lite
8	2	nova 4
9	2	Mate 20 X
10	2	Enjoy 9
11	2	nova 2s
12	2	Mate 10
13	3	iPhone 5
14	3	iPhone 6
15	3	iPhone 7
16	3	iPhone 8
17	3	iPhone 9
18	3	iPhone X
19	4	8.1
20	4	106
21	4	3.1 Plus
22	4	7.1
23	4	6.1
24	5	Q9
25	5	V40 ThinQ
26	5	Candy
27	5	G7 Fit
28	5	G7 One
29	6	Xperia XZ3
30	6	Xperio XA2 Plus
31	6	XPeria XZ2 Premium
32	6	XPeria XZ2
33	6	XPeria L2
34	7	Desire 12s
35	7	Exodus 1
36	7	U12 Life
37	7	U12+
38	7	U11 Eyes
39	8	KEY2 LE
40	8	Evolve X
41	8	Motion
42	8	Aurora
43	8	KEyone
\.


--
-- Data for Name: orden_detalles; Type: TABLE DATA; Schema: public; Owner: usuario
--

COPY public.orden_detalles (id_orden, id_reparacion_modelo) FROM stdin;
1	1
1	4
2	5
\.


--
-- Data for Name: ordenes; Type: TABLE DATA; Schema: public; Owner: usuario
--

COPY public.ordenes (id_orden, id_modelo_telefono, id_tienda, fecha, id_estado, id_tecnico) FROM stdin;
2	3	1	2019-01-27	1	1
1	1	1	2019-01-27	3	1
\.


--
-- Data for Name: reparaciones; Type: TABLE DATA; Schema: public; Owner: usuario
--

COPY public.reparaciones (id_reparacion, nombre_reparacion) FROM stdin;
1	Arreglar pantalla
2	Sustituir batería
3	Reparar microfono
4	Reparar altavoz
5	Limpieza
6	Liberar telefono
\.


--
-- Data for Name: tecnicos; Type: TABLE DATA; Schema: public; Owner: usuario
--

COPY public.tecnicos (id_tecnico, nombre_tecnico) FROM stdin;
1	Pepe Pablos
2	Miguel Rubio
\.


--
-- Data for Name: tiendas; Type: TABLE DATA; Schema: public; Owner: usuario
--

COPY public.tiendas (id_tienda, direccion_tienda, ciudad_tienda, pais_tienda, nombre_tienda) FROM stdin;
1	Av. de Portugal 1A	Palma de Mallorca	España	EDIB
\.


--
-- Name: estado_id_estado_seq; Type: SEQUENCE SET; Schema: public; Owner: usuario
--

SELECT pg_catalog.setval('public.estado_id_estado_seq', 3, true);


--
-- Name: marcas_telefono_id_marca_telefono_seq; Type: SEQUENCE SET; Schema: public; Owner: usuario
--

SELECT pg_catalog.setval('public.marcas_telefono_id_marca_telefono_seq', 8, true);


--
-- Name: modelo_reparacion_id_modelo_reparacion_seq; Type: SEQUENCE SET; Schema: public; Owner: usuario
--

SELECT pg_catalog.setval('public.modelo_reparacion_id_modelo_reparacion_seq', 11, true);


--
-- Name: modelo_reparacion_id_modelo_telefono_seq; Type: SEQUENCE SET; Schema: public; Owner: usuario
--

SELECT pg_catalog.setval('public.modelo_reparacion_id_modelo_telefono_seq', 1, false);


--
-- Name: modelo_reparacion_id_reparacion_seq; Type: SEQUENCE SET; Schema: public; Owner: usuario
--

SELECT pg_catalog.setval('public.modelo_reparacion_id_reparacion_seq', 1, false);


--
-- Name: modelo_telefono_id_modelo_telefono_seq; Type: SEQUENCE SET; Schema: public; Owner: usuario
--

SELECT pg_catalog.setval('public.modelo_telefono_id_modelo_telefono_seq', 43, true);


--
-- Name: modelo_telefono_marca_modelo_telefono_seq; Type: SEQUENCE SET; Schema: public; Owner: usuario
--

SELECT pg_catalog.setval('public.modelo_telefono_marca_modelo_telefono_seq', 1, false);


--
-- Name: orden_detalles_id_orden_seq; Type: SEQUENCE SET; Schema: public; Owner: usuario
--

SELECT pg_catalog.setval('public.orden_detalles_id_orden_seq', 1, false);


--
-- Name: orden_detalles_id_reparacion_modelo_seq; Type: SEQUENCE SET; Schema: public; Owner: usuario
--

SELECT pg_catalog.setval('public.orden_detalles_id_reparacion_modelo_seq', 1, false);


--
-- Name: ordenes_estado_seq; Type: SEQUENCE SET; Schema: public; Owner: usuario
--

SELECT pg_catalog.setval('public.ordenes_estado_seq', 1, false);


--
-- Name: ordenes_id_modelo_telefono_seq; Type: SEQUENCE SET; Schema: public; Owner: usuario
--

SELECT pg_catalog.setval('public.ordenes_id_modelo_telefono_seq', 1, false);


--
-- Name: ordenes_id_orden_seq; Type: SEQUENCE SET; Schema: public; Owner: usuario
--

SELECT pg_catalog.setval('public.ordenes_id_orden_seq', 2, true);


--
-- Name: ordenes_id_tecnico_seq; Type: SEQUENCE SET; Schema: public; Owner: usuario
--

SELECT pg_catalog.setval('public.ordenes_id_tecnico_seq', 1, false);


--
-- Name: ordenes_id_tienda_seq; Type: SEQUENCE SET; Schema: public; Owner: usuario
--

SELECT pg_catalog.setval('public.ordenes_id_tienda_seq', 1, false);


--
-- Name: reparaciones_id_reparacion_seq; Type: SEQUENCE SET; Schema: public; Owner: usuario
--

SELECT pg_catalog.setval('public.reparaciones_id_reparacion_seq', 6, true);


--
-- Name: tecnicos_id_tecnico_seq; Type: SEQUENCE SET; Schema: public; Owner: usuario
--

SELECT pg_catalog.setval('public.tecnicos_id_tecnico_seq', 2, true);


--
-- Name: tiendas_id_tienda_seq; Type: SEQUENCE SET; Schema: public; Owner: usuario
--

SELECT pg_catalog.setval('public.tiendas_id_tienda_seq', 1, true);


--
-- Name: estado estado_pkey; Type: CONSTRAINT; Schema: public; Owner: usuario
--

ALTER TABLE ONLY public.estado
    ADD CONSTRAINT estado_pkey PRIMARY KEY (id_estado);


--
-- Name: marcas_telefono marcas_telefono_pkey; Type: CONSTRAINT; Schema: public; Owner: usuario
--

ALTER TABLE ONLY public.marcas_telefono
    ADD CONSTRAINT marcas_telefono_pkey PRIMARY KEY (id_marca_telefono);


--
-- Name: modelo_reparacion modelo_reparacion_pkey; Type: CONSTRAINT; Schema: public; Owner: usuario
--

ALTER TABLE ONLY public.modelo_reparacion
    ADD CONSTRAINT modelo_reparacion_pkey PRIMARY KEY (id_modelo_reparacion);


--
-- Name: modelo_telefono modelo_telefono_pkey; Type: CONSTRAINT; Schema: public; Owner: usuario
--

ALTER TABLE ONLY public.modelo_telefono
    ADD CONSTRAINT modelo_telefono_pkey PRIMARY KEY (id_modelo_telefono);


--
-- Name: orden_detalles orden_detalles_pkey; Type: CONSTRAINT; Schema: public; Owner: usuario
--

ALTER TABLE ONLY public.orden_detalles
    ADD CONSTRAINT orden_detalles_pkey PRIMARY KEY (id_orden, id_reparacion_modelo);


--
-- Name: ordenes ordenes_pkey; Type: CONSTRAINT; Schema: public; Owner: usuario
--

ALTER TABLE ONLY public.ordenes
    ADD CONSTRAINT ordenes_pkey PRIMARY KEY (id_orden);


--
-- Name: reparaciones reparaciones_pkey; Type: CONSTRAINT; Schema: public; Owner: usuario
--

ALTER TABLE ONLY public.reparaciones
    ADD CONSTRAINT reparaciones_pkey PRIMARY KEY (id_reparacion);


--
-- Name: tecnicos tecnicos_pkey; Type: CONSTRAINT; Schema: public; Owner: usuario
--

ALTER TABLE ONLY public.tecnicos
    ADD CONSTRAINT tecnicos_pkey PRIMARY KEY (id_tecnico);


--
-- Name: tiendas tiendas_pkey; Type: CONSTRAINT; Schema: public; Owner: usuario
--

ALTER TABLE ONLY public.tiendas
    ADD CONSTRAINT tiendas_pkey PRIMARY KEY (id_tienda);


--
-- Name: modelo_reparacion fK_modRep_modelo; Type: FK CONSTRAINT; Schema: public; Owner: usuario
--

ALTER TABLE ONLY public.modelo_reparacion
    ADD CONSTRAINT "fK_modRep_modelo" FOREIGN KEY (id_modelo_telefono) REFERENCES public.modelo_telefono(id_modelo_telefono) ON UPDATE CASCADE ON DELETE RESTRICT;


--
-- Name: orden_detalles fk_detalles_orden; Type: FK CONSTRAINT; Schema: public; Owner: usuario
--

ALTER TABLE ONLY public.orden_detalles
    ADD CONSTRAINT fk_detalles_orden FOREIGN KEY (id_orden) REFERENCES public.ordenes(id_orden) ON UPDATE RESTRICT ON DELETE RESTRICT;


--
-- Name: orden_detalles fk_detalles_reparaciones; Type: FK CONSTRAINT; Schema: public; Owner: usuario
--

ALTER TABLE ONLY public.orden_detalles
    ADD CONSTRAINT fk_detalles_reparaciones FOREIGN KEY (id_reparacion_modelo) REFERENCES public.modelo_reparacion(id_modelo_reparacion) ON UPDATE RESTRICT ON DELETE RESTRICT;


--
-- Name: modelo_reparacion fk_modRep_reparacion; Type: FK CONSTRAINT; Schema: public; Owner: usuario
--

ALTER TABLE ONLY public.modelo_reparacion
    ADD CONSTRAINT "fk_modRep_reparacion" FOREIGN KEY (id_reparacion) REFERENCES public.reparaciones(id_reparacion) ON UPDATE CASCADE ON DELETE RESTRICT;


--
-- Name: modelo_telefono fk_modelo_marca_telefono; Type: FK CONSTRAINT; Schema: public; Owner: usuario
--

ALTER TABLE ONLY public.modelo_telefono
    ADD CONSTRAINT fk_modelo_marca_telefono FOREIGN KEY (id_marca_modelo_telefono) REFERENCES public.marcas_telefono(id_marca_telefono) ON UPDATE CASCADE ON DELETE RESTRICT;


--
-- Name: ordenes fk_orden_estado; Type: FK CONSTRAINT; Schema: public; Owner: usuario
--

ALTER TABLE ONLY public.ordenes
    ADD CONSTRAINT fk_orden_estado FOREIGN KEY (id_estado) REFERENCES public.estado(id_estado) ON UPDATE RESTRICT ON DELETE RESTRICT;


--
-- Name: ordenes fk_orden_modelo; Type: FK CONSTRAINT; Schema: public; Owner: usuario
--

ALTER TABLE ONLY public.ordenes
    ADD CONSTRAINT fk_orden_modelo FOREIGN KEY (id_modelo_telefono) REFERENCES public.modelo_telefono(id_modelo_telefono) ON UPDATE CASCADE ON DELETE RESTRICT;


--
-- Name: ordenes fk_orden_tecnico; Type: FK CONSTRAINT; Schema: public; Owner: usuario
--

ALTER TABLE ONLY public.ordenes
    ADD CONSTRAINT fk_orden_tecnico FOREIGN KEY (id_tecnico) REFERENCES public.tecnicos(id_tecnico) ON UPDATE CASCADE ON DELETE RESTRICT;


--
-- Name: ordenes fk_orden_tienda; Type: FK CONSTRAINT; Schema: public; Owner: usuario
--

ALTER TABLE ONLY public.ordenes
    ADD CONSTRAINT fk_orden_tienda FOREIGN KEY (id_tienda) REFERENCES public.tiendas(id_tienda) ON UPDATE CASCADE ON DELETE RESTRICT;


--
-- PostgreSQL database dump complete
--

