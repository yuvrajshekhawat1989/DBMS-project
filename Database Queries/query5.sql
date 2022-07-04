with co_authors(coauthor_name,rp_index) as
(select author_name,rp_index
from written_by
where rank=0 )

select  distinct (c1.coauthor_name, c2.coauthor_name)
from co_authors as c1,co_authors as c2
where c1.rp_index = c2.rp_index and c1.coauthor_name != c2.coauthor_name
group by c1.coauthor_name, c2.coauthor_name
having count((c1.coauthor_name, c2.coauthor_name))>1;
