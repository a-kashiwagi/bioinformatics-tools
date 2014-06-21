create table discovered_gene(
    s           bigint,
    e           bigint,
    strand      varchar(1),
    length      bigint,
    pid         bigint,
    gene        varchar(128),
    synonym    varchar(128),
    code        varchar(128),
    cog         varchar(128),
    product     varchar(1024)
);
