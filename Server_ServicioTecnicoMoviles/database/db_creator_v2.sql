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
-- Name: ordenes; Type: TABLE; Schema: public; Owner: usuario
--

CREATE TABLE public.ordenes (
    orden_id integer NOT NULL,
    modelo_id integer NOT NULL,
    tienda_id integer NOT NULL,
    estado_id integer DEFAULT 1,
    tecnico_id integer DEFAULT 1,
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
-- Name: ordenes orden_id; Type: DEFAULT; Schema: public; Owner: usuario
--

ALTER TABLE ONLY public.ordenes ALTER COLUMN orden_id SET DEFAULT nextval('public.ordenes_orden_id_seq'::regclass);


--
-- Data for Name: ordenes; Type: TABLE DATA; Schema: public; Owner: usuario
--

COPY public.ordenes (orden_id, modelo_id, tienda_id, estado_id, tecnico_id, orden_finalizada) FROM stdin;
1	7	1	1	1	f
3	7	1	3	1	f
4	1	1	3	1	f
5	7	1	3	1	f
6	1	1	2	1	f
2	1	1	2	1	f
7	9	1	1	1	f
8	7	1	1	1	f
9	8	1	1	1	f
10	6	1	1	1	f
11	1	1	1	1	f
12	1	1	1	1	f
13	1	1	1	1	f
14	1	1	1	1	f
\.


--
-- Name: ordenes_orden_id_seq; Type: SEQUENCE SET; Schema: public; Owner: usuario
--

SELECT pg_catalog.setval('public.ordenes_orden_id_seq', 14, true);


--
-- Name: ordenes ordenes_pkey; Type: CONSTRAINT; Schema: public; Owner: usuario
--

ALTER TABLE ONLY public.ordenes
    ADD CONSTRAINT ordenes_pkey PRIMARY KEY (orden_id);


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

