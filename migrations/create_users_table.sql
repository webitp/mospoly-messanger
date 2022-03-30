CREATE TABLE IF NOT EXISTS public.users
(
    id integer NOT NULL,
    phone text COLLATE pg_catalog."default" NOT NULL,
    username text COLLATE pg_catalog."default",
    online boolean DEFAULT false,
    created_at timestamp with time zone DEFAULT CURRENT_TIMESTAMP,
    CONSTRAINT users_pkey PRIMARY KEY (id)
)

ALTER TABLE IF EXISTS public.users
    OWNER to postgres;