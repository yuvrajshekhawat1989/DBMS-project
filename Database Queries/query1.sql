SELECT index.rp_index,research_paper.rp_index,title,year,abstract,venue,author_name
FROM (SELECT rp_index FROM research_paper) as index,research_paper,authors
WHERE (index.rp_index,research_paper.rp_index) in 
(SELECT cited_rp_index,rp_index
FROM citations)
AND
(research_paper.rp_index,author_name) in 
(SELECT rp_index,author_name
FROM written_by)
ORDER BY index.rp_index;
