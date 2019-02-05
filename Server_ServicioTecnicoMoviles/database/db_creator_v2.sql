 
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
-- Name: tecnicos tecnico_id; Type: DEFAULT; Schema: public; Owner: usuario
--

ALTER TABLE ONLY public.tecnicos ALTER COLUMN tecnico_id SET DEFAULT nextval('public.tecnicos_tecnico_id_seq'::regclass);


--
-- Name: tiendas tienda_id; Type: DEFAULT; Schema: public; Owner: usuario
--

ALTER TABLE ONLY public.tiendas ALTER COLUMN tienda_id SET DEFAULT nextval('public.tiendas_tienda_id_seq'::regclass);


--
-- Name: estados estados_pkey; Type: CONSTRAINT; Schema: public; Owner: usuario
--

ALTER TABLE ONLY public.estados
    ADD CONSTRAINT estados_pkey PRIMARY KEY (estado_id);


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
-- PostgreSQL database dump complete
--

