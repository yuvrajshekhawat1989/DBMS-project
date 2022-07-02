CREATE TABLE research_paper(
    rp_index INTEGER PRIMARY KEY,
    title VARCHAR(500),
    year SMALLINT,
    abstract VARCHAR(200000),
    venue VARCHAR(500),
    author_exist BOOLEAN
);
CREATE TABLE authors(
    author_name VARCHAR(200) PRIMARY KEY
);
CREATE TABLE written_by(
    rp_index INTEGER,
    author_name VARCHAR(200),
    rank SMALLINT,
    PRIMARY KEY(rp_index,author_name),
    FOREIGN KEY(rp_index) REFERENCES research_paper,
    FOREIGN KEY(author_name) REFERENCES authors
);
CREATE TABLE citations(
    rp_index INTEGER,
    cited_rp_index INTEGER,
    PRIMARY KEY(rp_index,cited_rp_index),
    FOREIGN KEY(rp_index) REFERENCES research_paper,
    FOREIGN KEY(cited_rp_index) REFERENCES research_paper
);