with cit(cindex) as
( select cited_rp_index 
 from citations 
group by cited_rp_index
order by count(cited_rp_index) desc
limit 20)

SELECT research_paper.rp_index, research_paper.title, research_paper.year ,research_paper.abstract, research_paper.venue 
from research_paper,cit
where research_paper.rp_index = cit.cindex;
