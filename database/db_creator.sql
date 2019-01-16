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
    fecha date NOT NULL,
    id_estado integer NOT NULL,
    id_tecnico integer NOT NULL
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
    pais_tienda text NOT NULL
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
-- Name: modelo_telefono id_marca_modelo_telefono; Type: DEFAULT; Schema: public; Owner: usuario
--

ALTER TABLE ONLY public.modelo_telefono ALTER COLUMN id_marca_modelo_telefono SET DEFAULT nextval('public.modelo_telefono_marca_modelo_telefono_seq'::regclass);


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

