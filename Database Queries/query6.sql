with author_cit(author,cited_author) as 
(select w1.author_name, w2.author_name
from citations as c, written_by as w1, written_by as w2
where c.rp_index=w1.rp_index and c.cited_rp_index= w2.rp_index and w1.author_name !=w2.author_name)


select a1.author, a2.author, a3.author
from author_cit as a1,author_cit as a2,author_cit as a3
where (a1.cited_author= a2.author or a2.cited_author= a1.author) 
and  (a2.cited_author= a3.author or a3.cited_author= a2.author)
and  (a3.cited_author= a1.author or a1.cited_author= a3.author)
and a1.author > a2.author and a2.author > a3.author;
