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
-- Name: estados; Type: TABLE; Schema: public; Owner: usuario
--

CREATE TABLE public.estados (
    estado_id integer NOT NULL,
    estado_nombre character varying NOT NULL,
    estado_activo boolean DEFAULT true NOT NULL
);


ALTER TABLE public.estados OWNER TO usuario;

--
-- Name: estados_estado_id_seq; Type: SEQUENCE; Schema: public; Owner: usuario
--

CREATE SEQUENCE public.estados_estado_id_seq
    AS integer
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER TABLE public.estados_estado_id_seq OWNER TO usuario;

--
-- Name: estados_estado_id_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: usuario
--

ALTER SEQUENCE public.estados_estado_id_seq OWNED BY public.estados.estado_id;


--
-- Name: marcas; Type: TABLE; Schema: public; Owner: usuario
--

CREATE TABLE public.marcas (
    marca_id integer NOT NULL,
    marca_nombre character varying NOT NULL,
    marca_activo boolean DEFAULT true NOT NULL
);


ALTER TABLE public.marcas OWNER TO usuario;

--
-- Name: marcas_marca_id_seq; Type: SEQUENCE; Schema: public; Owner: usuario
--

CREATE SEQUENCE public.marcas_marca_id_seq
    AS integer
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER TABLE public.marcas_marca_id_seq OWNER TO usuario;

--
-- Name: marcas_marca_id_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: usuario
--

ALTER SEQUENCE public.marcas_marca_id_seq OWNED BY public.marcas.marca_id;


--
-- Name: modelo_reparaciones; Type: TABLE; Schema: public; Owner: usuario
--

CREATE TABLE public.modelo_reparaciones (
    modelo_reparaciones_id integer NOT NULL,
    modelo_id integer NOT NULL,
    reparacion_id integer NOT NULL,
    modelo_reparaciones_activo boolean DEFAULT true NOT NULL
);


ALTER TABLE public.modelo_reparaciones OWNER TO usuario;

--
-- Name: modeloReparaciones_modeloReparaciones_id_seq; Type: SEQUENCE; Schema: public; Owner: usuario
--

CREATE SEQUENCE public."modeloReparaciones_modeloReparaciones_id_seq"
    AS integer
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER TABLE public."modeloReparaciones_modeloReparaciones_id_seq" OWNER TO usuario;

--
-- Name: modeloReparaciones_modeloReparaciones_id_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: usuario
--

ALTER SEQUENCE public."modeloReparaciones_modeloReparaciones_id_seq" OWNED BY public.modelo_reparaciones.modelo_reparaciones_id;


--
-- Name: modelos; Type: TABLE; Schema: public; Owner: usuario
--

CREATE TABLE public.modelos (
    modelo_id integer NOT NULL,
    modelo_nombre character varying NOT NULL,
    marca_id integer NOT NULL,
    modelo_activo boolean DEFAULT true NOT NULL
);


ALTER TABLE public.modelos OWNER TO usuario;

--
-- Name: modelos_modelo_id_seq; Type: SEQUENCE; Schema: public; Owner: usuario
--

CREATE SEQUENCE public.modelos_modelo_id_seq
    AS integer
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER TABLE public.modelos_modelo_id_seq OWNER TO usuario;

--
-- Name: modelos_modelo_id_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: usuario
--

ALTER SEQUENCE public.modelos_modelo_id_seq OWNED BY public.modelos.modelo_id;


--
-- Name: orden_detalles; Type: TABLE; Schema: public; Owner: usuario
--

CREATE TABLE public.orden_detalles (
    orden_id integer NOT NULL,
    modelo_reparaciones_id integer NOT NULL
);


ALTER TABLE public.orden_detalles OWNER TO usuario;

--
-- Name: ordenes; Type: TABLE; Schema: public; Owner: usuario
--

CREATE TABLE public.ordenes (
    orden_id integer NOT NULL,
    modelo_id integer NOT NULL,
    tienda_id integer NOT NULL,
    estado_id integer NOT NULL,
    tecnico_id integer NOT NULL,
    orden_finalizada boolean DEFAULT false
);


ALTER TABLE public.ordenes OWNER TO usuario;

--
-- Name: ordenes_orden_id_seq; Type: SEQUENCE; Schema: public; Owner: usuario
--

CREATE SEQUENCE public.ordenes_orden_id_seq
    AS integer
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER TABLE public.ordenes_orden_id_seq OWNER TO usuario;

--
-- Name: ordenes_orden_id_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: usuario
--

ALTER SEQUENCE public.ordenes_orden_id_seq OWNED BY public.ordenes.orden_id;


--
-- Name: reparaciones; Type: TABLE; Schema: public; Owner: usuario
--

CREATE TABLE public.reparaciones (
    reparacion_id integer NOT NULL,
    reparacion_nombre character varying NOT NULL
);


ALTER TABLE public.reparaciones OWNER TO usuario;

--
-- Name: reparaciones_reparacion_id_seq; Type: SEQUENCE; Schema: public; Owner: usuario
--

CREATE SEQUENCE public.reparaciones_reparacion_id_seq
    AS integer
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER TABLE public.reparaciones_reparacion_id_seq OWNER TO usuario;

--
-- Name: reparaciones_reparacion_id_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: usuario
--

ALTER SEQUENCE public.reparaciones_reparacion_id_seq OWNED BY public.reparaciones.reparacion_id;


--
-- Name: tecnicos; Type: TABLE; Schema: public; Owner: usuario
--

CREATE TABLE public.tecnicos (
    tecnico_id integer NOT NULL,
    tecnico_nombre character varying NOT NULL,
    tecnico_usuario character varying NOT NULL,
    tecnico_password character varying NOT NULL,
    tecnico_activo boolean DEFAULT true NOT NULL
);


ALTER TABLE public.tecnicos OWNER TO usuario;

--
-- Name: tecnicos_tecnico_id_seq; Type: SEQUENCE; Schema: public; Owner: usuario
--

CREATE SEQUENCE public.tecnicos_tecnico_id_seq
    AS integer
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER TABLE public.tecnicos_tecnico_id_seq OWNER TO usuario;

--
-- Name: tecnicos_tecnico_id_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: usuario
--

ALTER SEQUENCE public.tecnicos_tecnico_id_seq OWNED BY public.tecnicos.tecnico_id;


--
-- Name: tiendas; Type: TABLE; Schema: public; Owner: usuario
--

CREATE TABLE public.tiendas (
    tienda_id integer NOT NULL,
    tienda_nombre character varying NOT NULL,
    tienda_user character varying NOT NULL,
    tienda_password character varying NOT NULL,
    tienda_direccion character varying NOT NULL,
    tienda_activo boolean DEFAULT true NOT NULL
);


ALTER TABLE public.tiendas OWNER TO usuario;

--
-- Name: tiendas_tienda_id_seq; Type: SEQUENCE; Schema: public; Owner: usuario
--

CREATE SEQUENCE public.tiendas_tienda_id_seq
    AS integer
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER TABLE public.tiendas_tienda_id_seq OWNER TO usuario;

--
-- Name: tiendas_tienda_id_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: usuario
--

ALTER SEQUENCE public.tiendas_tienda_id_seq OWNED BY public.tiendas.tienda_id;


--
-- Name: estados estado_id; Type: DEFAULT; Schema: public; Owner: usuario
--

ALTER TABLE ONLY public.estados ALTER COLUMN estado_id SET DEFAULT nextval('public.estados_estado_id_seq'::regclass);


--
-- Name: marcas marca_id; Type: DEFAULT; Schema: public; Owner: usuario
--

ALTER TABLE ONLY public.marcas ALTER COLUMN marca_id SET DEFAULT nextval('public.marcas_marca_id_seq'::regclass);


--
-- Name: modelo_reparaciones modelo_reparaciones_id; Type: DEFAULT; Schema: public; Owner: usuario
--

ALTER TABLE ONLY public.modelo_reparaciones ALTER COLUMN modelo_reparaciones_id SET DEFAULT nextval('public."modeloReparaciones_modeloReparaciones_id_seq"'::regclass);


--
-- Name: modelos modelo_id; Type: DEFAULT; Schema: public; Owner: usuario
--

ALTER TABLE ONLY public.modelos ALTER COLUMN modelo_id SET DEFAULT nextval('public.modelos_modelo_id_seq'::regclass);


--
-- Name: ordenes orden_id; Type: DEFAULT; Schema: public; Owner: usuario
--

ALTER TABLE ONLY public.ordenes ALTER COLUMN orden_id SET DEFAULT nextval('public.ordenes_orden_id_seq'::regclass);


--
-- Name: reparaciones reparacion_id; Type: DEFAULT; Schema: public; Owner: usuario
--

ALTER TABLE ONLY public.reparaciones ALTER COLUMN reparacion_id SET DEFAULT nextval('public.reparaciones_reparacion_id_seq'::regclass);


--
-- Name: tecnicos tecnico_id; Type: DEFAULT; Schema: public; Owner: usuario
--

ALTER TABLE ONLY public.tecnicos ALTER COLUMN tecnico_id SET DEFAULT nextval('public.tecnicos_tecnico_id_seq'::regclass);


--
-- Name: tiendas tienda_id; Type: DEFAULT; Schema: public; Owner: usuario
--

ALTER TABLE ONLY public.tiendas ALTER COLUMN tienda_id SET DEFAULT nextval('public.tiendas_tienda_id_seq'::regclass);


--
-- Data for Name: estados; Type: TABLE DATA; Schema: public; Owner: usuario
--

COPY public.estados (estado_id, estado_nombre, estado_activo) FROM stdin;
1	DE CAMINO AL TECNICO	t
2	REPARANDO	t
3	DE CAMINO A LA TIENDA	t
\.


--
-- Data for Name: marcas; Type: TABLE DATA; Schema: public; Owner: usuario
--

COPY public.marcas (marca_id, marca_nombre, marca_activo) FROM stdin;
1	Samsung	t
2	Apple	t
3	Motorola	t
4	Nokia	t
\.


--
-- Data for Name: modelo_reparaciones; Type: TABLE DATA; Schema: public; Owner: usuario
--

COPY public.modelo_reparaciones (modelo_reparaciones_id, modelo_id, reparacion_id, modelo_reparaciones_activo) FROM stdin;
1	1	1	t
2	1	2	t
3	1	4	t
4	2	1	t
5	2	3	t
6	3	1	t
7	3	2	t
8	4	4	t
9	5	1	t
10	5	2	t
11	5	3	t
12	6	1	t
13	6	3	t
14	6	2	t
15	7	2	t
16	7	1	t
17	8	4	t
18	8	2	t
19	9	1	t
20	9	3	t
\.


--
-- Data for Name: modelos; Type: TABLE DATA; Schema: public; Owner: usuario
--

COPY public.modelos (modelo_id, modelo_nombre, marca_id, modelo_activo) FROM stdin;
1	Samsung Modelo 1	1	t
2	Samsung Modelo 2	1	t
3	Samsung Modelo 3	1	t
4	Apple Modelo 1	2	t
5	Apple Modelo 2	2	t
6	Apple Modelo 3	2	t
7	Motorola Modelo 1	3	t
8	Nokia Modelo 1	4	t
9	Nokia Modelo 2	4	t
\.


--
-- Data for Name: orden_detalles; Type: TABLE DATA; Schema: public; Owner: usuario
--

COPY public.orden_detalles (orden_id, modelo_reparaciones_id) FROM stdin;
\.


--
-- Data for Name: ordenes; Type: TABLE DATA; Schema: public; Owner: usuario
--

COPY public.ordenes (orden_id, modelo_id, tienda_id, estado_id, tecnico_id, orden_finalizada) FROM stdin;
\.


--
-- Data for Name: reparaciones; Type: TABLE DATA; Schema: public; Owner: usuario
--

COPY public.reparaciones (reparacion_id, reparacion_nombre) FROM stdin;
1	Arreglar pantalla
2	Cambiar bateria
3	Arreglar wifi
4	Limpieza interior
\.


--
-- Data for Name: tecnicos; Type: TABLE DATA; Schema: public; Owner: usuario
--

COPY public.tecnicos (tecnico_id, tecnico_nombre, tecnico_usuario, tecnico_password, tecnico_activo) FROM stdin;
1	Tecnico 1	tec1	tec1	t
\.


--
-- Data for Name: tiendas; Type: TABLE DATA; Schema: public; Owner: usuario
--

COPY public.tiendas (tienda_id, tienda_nombre, tienda_user, tienda_password, tienda_direccion, tienda_activo) FROM stdin;
1	EDIB	edib	edib	Calle inexistente fjldskfjañldsfs	t
2	PRUEBA	prueba	prueba	Calle imaginaria	t
\.


--
-- Name: estados_estado_id_seq; Type: SEQUENCE SET; Schema: public; Owner: usuario
--

SELECT pg_catalog.setval('public.estados_estado_id_seq', 3, true);


--
-- Name: marcas_marca_id_seq; Type: SEQUENCE SET; Schema: public; Owner: usuario
--

SELECT pg_catalog.setval('public.marcas_marca_id_seq', 4, true);


--
-- Name: modeloReparaciones_modeloReparaciones_id_seq; Type: SEQUENCE SET; Schema: public; Owner: usuario
--

SELECT pg_catalog.setval('public."modeloReparaciones_modeloReparaciones_id_seq"', 20, true);


--
-- Name: modelos_modelo_id_seq; Type: SEQUENCE SET; Schema: public; Owner: usuario
--

SELECT pg_catalog.setval('public.modelos_modelo_id_seq', 9, true);


--
-- Name: ordenes_orden_id_seq; Type: SEQUENCE SET; Schema: public; Owner: usuario
--

SELECT pg_catalog.setval('public.ordenes_orden_id_seq', 1, false);


--
-- Name: reparaciones_reparacion_id_seq; Type: SEQUENCE SET; Schema: public; Owner: usuario
--

SELECT pg_catalog.setval('public.reparaciones_reparacion_id_seq', 4, true);


--
-- Name: tecnicos_tecnico_id_seq; Type: SEQUENCE SET; Schema: public; Owner: usuario
--

SELECT pg_catalog.setval('public.tecnicos_tecnico_id_seq', 1, true);


--
-- Name: tiendas_tienda_id_seq; Type: SEQUENCE SET; Schema: public; Owner: usuario
--

SELECT pg_catalog.setval('public.tiendas_tienda_id_seq', 2, true);


--
-- Name: estados estados_pkey; Type: CONSTRAINT; Schema: public; Owner: usuario
--

ALTER TABLE ONLY public.estados
    ADD CONSTRAINT estados_pkey PRIMARY KEY (estado_id);


--
-- Name: marcas marcas_pkey; Type: CONSTRAINT; Schema: public; Owner: usuario
--

ALTER TABLE ONLY public.marcas
    ADD CONSTRAINT marcas_pkey PRIMARY KEY (marca_id);


--
-- Name: modelo_reparaciones modelo_reparaciones_pkey; Type: CONSTRAINT; Schema: public; Owner: usuario
--

ALTER TABLE ONLY public.modelo_reparaciones
    ADD CONSTRAINT modelo_reparaciones_pkey PRIMARY KEY (modelo_reparaciones_id);


--
-- Name: modelos modelos_pkey; Type: CONSTRAINT; Schema: public; Owner: usuario
--

ALTER TABLE ONLY public.modelos
    ADD CONSTRAINT modelos_pkey PRIMARY KEY (modelo_id);


--
-- Name: orden_detalles ordenDetalles_pkey; Type: CONSTRAINT; Schema: public; Owner: usuario
--

ALTER TABLE ONLY public.orden_detalles
    ADD CONSTRAINT "ordenDetalles_pkey" PRIMARY KEY (orden_id, modelo_reparaciones_id);


--
-- Name: ordenes ordenes_pkey; Type: CONSTRAINT; Schema: public; Owner: usuario
--

ALTER TABLE ONLY public.ordenes
    ADD CONSTRAINT ordenes_pkey PRIMARY KEY (orden_id);


--
-- Name: reparaciones reparaciones_pkey; Type: CONSTRAINT; Schema: public; Owner: usuario
--

ALTER TABLE ONLY public.reparaciones
    ADD CONSTRAINT reparaciones_pkey PRIMARY KEY (reparacion_id);


--
-- Name: tecnicos tecnicos_pkey; Type: CONSTRAINT; Schema: public; Owner: usuario
--

ALTER TABLE ONLY public.tecnicos
    ADD CONSTRAINT tecnicos_pkey PRIMARY KEY (tecnico_id);


--
-- Name: tecnicos tecnicos_tecnico_usuario_key; Type: CONSTRAINT; Schema: public; Owner: usuario
--

ALTER TABLE ONLY public.tecnicos
    ADD CONSTRAINT tecnicos_tecnico_usuario_key UNIQUE (tecnico_usuario);


--
-- Name: tiendas tiendas_pkey; Type: CONSTRAINT; Schema: public; Owner: usuario
--

ALTER TABLE ONLY public.tiendas
    ADD CONSTRAINT tiendas_pkey PRIMARY KEY (tienda_id);


--
-- Name: tiendas tiendas_tienda_user_key; Type: CONSTRAINT; Schema: public; Owner: usuario
--

ALTER TABLE ONLY public.tiendas
    ADD CONSTRAINT tiendas_tienda_user_key UNIQUE (tienda_user);


--
-- Name: modelo_reparaciones modeloReparaciones_modelo_id_fkey; Type: FK CONSTRAINT; Schema: public; Owner: usuario
--

ALTER TABLE ONLY public.modelo_reparaciones
    ADD CONSTRAINT "modeloReparaciones_modelo_id_fkey" FOREIGN KEY (modelo_id) REFERENCES public.modelos(modelo_id) ON UPDATE CASCADE ON DELETE RESTRICT;


--
-- Name: modelo_reparaciones modeloReparaciones_reparacion_id_fkey; Type: FK CONSTRAINT; Schema: public; Owner: usuario
--

ALTER TABLE ONLY public.modelo_reparaciones
    ADD CONSTRAINT "modeloReparaciones_reparacion_id_fkey" FOREIGN KEY (reparacion_id) REFERENCES public.reparaciones(reparacion_id) ON UPDATE CASCADE ON DELETE RESTRICT;


--
-- Name: modelos modelos_marca_id_fkey; Type: FK CONSTRAINT; Schema: public; Owner: usuario
--

ALTER TABLE ONLY public.modelos
    ADD CONSTRAINT modelos_marca_id_fkey FOREIGN KEY (marca_id) REFERENCES public.marcas(marca_id) ON UPDATE CASCADE ON DELETE RESTRICT;


--
-- Name: orden_detalles ordenDetalles_modelo_reparaciones_id_fkey; Type: FK CONSTRAINT; Schema: public; Owner: usuario
--

ALTER TABLE ONLY public.orden_detalles
    ADD CONSTRAINT "ordenDetalles_modelo_reparaciones_id_fkey" FOREIGN KEY (modelo_reparaciones_id) REFERENCES public.modelo_reparaciones(modelo_reparaciones_id) ON UPDATE CASCADE ON DELETE RESTRICT;


--
-- Name: orden_detalles ordenDetalles_orden_id_fkey; Type: FK CONSTRAINT; Schema: public; Owner: usuario
--

ALTER TABLE ONLY public.orden_detalles
    ADD CONSTRAINT "ordenDetalles_orden_id_fkey" FOREIGN KEY (orden_id) REFERENCES public.ordenes(orden_id) ON UPDATE CASCADE ON DELETE RESTRICT;


--
-- Name: ordenes ordenes_estado_id_fkey; Type: FK CONSTRAINT; Schema: public; Owner: usuario
--

ALTER TABLE ONLY public.ordenes
    ADD CONSTRAINT ordenes_estado_id_fkey FOREIGN KEY (estado_id) REFERENCES public.estados(estado_id) ON UPDATE CASCADE ON DELETE RESTRICT;


--
-- Name: ordenes ordenes_modelo_id_fkey; Type: FK CONSTRAINT; Schema: public; Owner: usuario
--

ALTER TABLE ONLY public.ordenes
    ADD CONSTRAINT ordenes_modelo_id_fkey FOREIGN KEY (modelo_id) REFERENCES public.modelos(modelo_id) ON UPDATE CASCADE ON DELETE RESTRICT;


--
-- Name: ordenes ordenes_tecnico_id_fkey; Type: FK CONSTRAINT; Schema: public; Owner: usuario
--

ALTER TABLE ONLY public.ordenes
    ADD CONSTRAINT ordenes_tecnico_id_fkey FOREIGN KEY (tecnico_id) REFERENCES public.tecnicos(tecnico_id) ON UPDATE CASCADE ON DELETE RESTRICT;


--
-- Name: ordenes ordenes_tienda_id_fkey; Type: FK CONSTRAINT; Schema: public; Owner: usuario
--

ALTER TABLE ONLY public.ordenes
    ADD CONSTRAINT ordenes_tienda_id_fkey FOREIGN KEY (tienda_id) REFERENCES public.tiendas(tienda_id) ON UPDATE CASCADE ON DELETE RESTRICT;


--
-- PostgreSQL database dump complete
--

