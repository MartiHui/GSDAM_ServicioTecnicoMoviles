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
-- Name: modelo_telefono id_modelo_telefono; Type: DEFAULT; Schema: public; Owner: usuario
--

ALTER TABLE ONLY public.modelo_telefono ALTER COLUMN id_modelo_telefono SET DEFAULT nextval('public.modelo_telefono_id_modelo_telefono_seq'::regclass);


--
-- Name: modelo_telefono id_marca_modelo_telefono; Type: DEFAULT; Schema: public; Owner: usuario
--

ALTER TABLE ONLY public.modelo_telefono ALTER COLUMN id_marca_modelo_telefono SET DEFAULT nextval('public.modelo_telefono_marca_modelo_telefono_seq'::regclass);


--
-- Name: modelo_telefono modelo_telefono_pkey; Type: CONSTRAINT; Schema: public; Owner: usuario
--

ALTER TABLE ONLY public.modelo_telefono
    ADD CONSTRAINT modelo_telefono_pkey PRIMARY KEY (id_modelo_telefono);


--
-- Name: modelo_telefono fk_modelo_marca_telefono; Type: FK CONSTRAINT; Schema: public; Owner: usuario
--

ALTER TABLE ONLY public.modelo_telefono
    ADD CONSTRAINT fk_modelo_marca_telefono FOREIGN KEY (id_marca_modelo_telefono) REFERENCES public.marcas_telefono(id_marca_telefono) ON UPDATE CASCADE ON DELETE RESTRICT;


--
-- PostgreSQL database dump complete
--

