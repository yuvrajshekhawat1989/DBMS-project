WITH answer(rp_index,second_level_cited_by) as
(SELECT second_level.cited_rp_index,citations.rp_index
FROM citations
INNER JOIN citations as second_level
ON citations.cited_rp_index=second_level.rp_index),
rp_paper(rp_index,title,year,venue,abstract,author_name) as
(SELECT research_paper.rp_index,research_paper.title,research_paper.year,
research_paper.venue,research_paper.abstract,written_by.author_name
FROM research_paper 
INNER JOIN written_by
ON research_paper.rp_index = written_by.rp_index)
SELECT answer.rp_index,answer.second_level_cited_by,rp_paper.title,rp_paper.year,
rp_paper.venue,rp_paper.abstract,rp_paper.author_name
FROM answer
LEFT JOIN rp_paper
ON answer.second_level_cited_by=rp_paper.rp_index
ORDER BY answer.rp_index;