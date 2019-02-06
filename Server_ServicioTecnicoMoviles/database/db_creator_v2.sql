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
-- Name: modeloReparaciones; Type: TABLE; Schema: public; Owner: usuario
--

CREATE TABLE public."modeloReparaciones" (
    "modeloReparaciones_id" integer NOT NULL,
    modelo_id integer NOT NULL,
    reparacion_id integer NOT NULL,
    "modeloReparaciones_activo" boolean DEFAULT true NOT NULL
);


ALTER TABLE public."modeloReparaciones" OWNER TO usuario;

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

ALTER SEQUENCE public."modeloReparaciones_modeloReparaciones_id_seq" OWNED BY public."modeloReparaciones"."modeloReparaciones_id";


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
-- Name: ordenDetalles; Type: TABLE; Schema: public; Owner: usuario
--

CREATE TABLE public."ordenDetalles" (
    orden_id integer NOT NULL,
    "modeloReparaciones_id" integer NOT NULL
);


ALTER TABLE public."ordenDetalles" OWNER TO usuario;

--
-- Name: ordenes; Type: TABLE; Schema: public; Owner: usuario
--

CREATE TABLE public.ordenes (
    orden_id integer NOT NULL,
    modelo_id integer NOT NULL,
    tienda_id integer NOT NULL,
    estado_id integer NOT NULL,
    tecnico_id integer NOT NULL
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
-- Name: modeloReparaciones modeloReparaciones_id; Type: DEFAULT; Schema: public; Owner: usuario
--

ALTER TABLE ONLY public."modeloReparaciones" ALTER COLUMN "modeloReparaciones_id" SET DEFAULT nextval('public."modeloReparaciones_modeloReparaciones_id_seq"'::regclass);


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
-- Name: modeloReparaciones modeloReparaciones_pkey; Type: CONSTRAINT; Schema: public; Owner: usuario
--

ALTER TABLE ONLY public."modeloReparaciones"
    ADD CONSTRAINT "modeloReparaciones_pkey" PRIMARY KEY ("modeloReparaciones_id");


--
-- Name: modelos modelos_pkey; Type: CONSTRAINT; Schema: public; Owner: usuario
--

ALTER TABLE ONLY public.modelos
    ADD CONSTRAINT modelos_pkey PRIMARY KEY (modelo_id);


--
-- Name: ordenDetalles ordenDetalles_pkey; Type: CONSTRAINT; Schema: public; Owner: usuario
--

ALTER TABLE ONLY public."ordenDetalles"
    ADD CONSTRAINT "ordenDetalles_pkey" PRIMARY KEY (orden_id, "modeloReparaciones_id");


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
-- Name: modeloReparaciones modeloReparaciones_modelo_id_fkey; Type: FK CONSTRAINT; Schema: public; Owner: usuario
--

ALTER TABLE ONLY public."modeloReparaciones"
    ADD CONSTRAINT "modeloReparaciones_modelo_id_fkey" FOREIGN KEY (modelo_id) REFERENCES public.modelos(modelo_id) ON UPDATE CASCADE ON DELETE RESTRICT;


--
-- Name: modeloReparaciones modeloReparaciones_reparacion_id_fkey; Type: FK CONSTRAINT; Schema: public; Owner: usuario
--

ALTER TABLE ONLY public."modeloReparaciones"
    ADD CONSTRAINT "modeloReparaciones_reparacion_id_fkey" FOREIGN KEY (reparacion_id) REFERENCES public.reparaciones(reparacion_id) ON UPDATE CASCADE ON DELETE RESTRICT;


--
-- Name: modelos modelos_marca_id_fkey; Type: FK CONSTRAINT; Schema: public; Owner: usuario
--

ALTER TABLE ONLY public.modelos
    ADD CONSTRAINT modelos_marca_id_fkey FOREIGN KEY (marca_id) REFERENCES public.marcas(marca_id) ON UPDATE CASCADE ON DELETE RESTRICT;


--
-- Name: ordenDetalles ordenDetalles_modeloReparaciones_id_fkey; Type: FK CONSTRAINT; Schema: public; Owner: usuario
--

ALTER TABLE ONLY public."ordenDetalles"
    ADD CONSTRAINT "ordenDetalles_modeloReparaciones_id_fkey" FOREIGN KEY ("modeloReparaciones_id") REFERENCES public."modeloReparaciones"("modeloReparaciones_id") ON UPDATE CASCADE ON DELETE RESTRICT;


--
-- Name: ordenDetalles ordenDetalles_orden_id_fkey; Type: FK CONSTRAINT; Schema: public; Owner: usuario
--

ALTER TABLE ONLY public."ordenDetalles"
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

