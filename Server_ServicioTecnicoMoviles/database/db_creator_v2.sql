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
-- Data for Name: estados; Type: TABLE DATA; Schema: public; Owner: usuario
--

COPY public.estados (estado_id, estado_nombre, estado_activo) FROM stdin;
\.


--
-- Data for Name: marcas; Type: TABLE DATA; Schema: public; Owner: usuario
--

COPY public.marcas (marca_id, marca_nombre, marca_activo) FROM stdin;
\.


--
-- Data for Name: modelos; Type: TABLE DATA; Schema: public; Owner: usuario
--

COPY public.modelos (modelo_id, modelo_nombre, marca_id, modelo_activo) FROM stdin;
\.


--
-- Data for Name: reparaciones; Type: TABLE DATA; Schema: public; Owner: usuario
--

COPY public.reparaciones (reparacion_id, reparacion_nombre) FROM stdin;
\.


--
-- Data for Name: modeloReparaciones; Type: TABLE DATA; Schema: public; Owner: usuario
--

COPY public."modeloReparaciones" ("modeloReparaciones_id", modelo_id, reparacion_id, "modeloReparaciones_activo") FROM stdin;
\.


--
-- Data for Name: tecnicos; Type: TABLE DATA; Schema: public; Owner: usuario
--

COPY public.tecnicos (tecnico_id, tecnico_nombre, tecnico_usuario, tecnico_password, tecnico_activo) FROM stdin;
\.


--
-- Data for Name: tiendas; Type: TABLE DATA; Schema: public; Owner: usuario
--

COPY public.tiendas (tienda_id, tienda_nombre, tienda_user, tienda_password, tienda_direccion, tienda_activo) FROM stdin;
\.


--
-- Data for Name: ordenes; Type: TABLE DATA; Schema: public; Owner: usuario
--

COPY public.ordenes (orden_id, modelo_id, tienda_id, estado_id, tecnico_id) FROM stdin;
\.


--
-- Data for Name: ordenDetalles; Type: TABLE DATA; Schema: public; Owner: usuario
--

COPY public."ordenDetalles" (orden_id, "modeloReparaciones_id") FROM stdin;
\.


--
-- Name: estados_estado_id_seq; Type: SEQUENCE SET; Schema: public; Owner: usuario
--

SELECT pg_catalog.setval('public.estados_estado_id_seq', 1, false);


--
-- Name: marcas_marca_id_seq; Type: SEQUENCE SET; Schema: public; Owner: usuario
--

SELECT pg_catalog.setval('public.marcas_marca_id_seq', 1, false);


--
-- Name: modeloReparaciones_modeloReparaciones_id_seq; Type: SEQUENCE SET; Schema: public; Owner: usuario
--

SELECT pg_catalog.setval('public."modeloReparaciones_modeloReparaciones_id_seq"', 1, false);


--
-- Name: modelos_modelo_id_seq; Type: SEQUENCE SET; Schema: public; Owner: usuario
--

SELECT pg_catalog.setval('public.modelos_modelo_id_seq', 1, false);


--
-- Name: ordenes_orden_id_seq; Type: SEQUENCE SET; Schema: public; Owner: usuario
--

SELECT pg_catalog.setval('public.ordenes_orden_id_seq', 1, false);


--
-- Name: reparaciones_reparacion_id_seq; Type: SEQUENCE SET; Schema: public; Owner: usuario
--

SELECT pg_catalog.setval('public.reparaciones_reparacion_id_seq', 1, false);


--
-- Name: tecnicos_tecnico_id_seq; Type: SEQUENCE SET; Schema: public; Owner: usuario
--

SELECT pg_catalog.setval('public.tecnicos_tecnico_id_seq', 1, false);


--
-- Name: tiendas_tienda_id_seq; Type: SEQUENCE SET; Schema: public; Owner: usuario
--

SELECT pg_catalog.setval('public.tiendas_tienda_id_seq', 1, false);


--
-- PostgreSQL database dump complete
--

