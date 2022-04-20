CREATE TABLE public.user_tokens
(
    id integer,
    user_id integer NOT NULL,
    token text NOT NULL,
    expired_at timestamp with time zone,
    created_at timestamp with time zone DEFAULT CURRENT_TIMESTAMP,
    PRIMARY KEY (id)
);

ALTER TABLE IF EXISTS public.user_tokens
    OWNER to postgres;