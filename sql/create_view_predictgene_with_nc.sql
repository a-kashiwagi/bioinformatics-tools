CREATE VIEW predictgene AS
    ((((((((((
SELECT s1n_n.sequence, s1n_n.s, s1n_n.e, s1n_n.score, false AS reverse, false AS amino_acid, 1 AS shift_num, s1n_n.nc FROM s1n_n
 UNION SELECT s1a_n.sequence, s1a_n.s, s1a_n.e, s1a_n.score, false AS reverse, true AS amino_acid, 1 AS shift_num, s1a_n.nc FROM s1a_n)
 UNION SELECT s2n_n.sequence, s2n_n.s, s2n_n.e, s2n_n.score, false AS reverse, false AS amino_acid, 2 AS shift_num, s2n_n.nc FROM s2n_n)
 UNION SELECT s2a_n.sequence, s2a_n.s, s2a_n.e, s2a_n.score, false AS reverse, true AS amino_acid, 2 AS shift_num, s2a_n.nc FROM s2a_n)
 UNION SELECT s3n_n.sequence, s3n_n.s, s3n_n.e, s3n_n.score, false AS reverse, false AS amino_acid, 3 AS shift_num, s3n_n.nc FROM s3n_n)
 UNION SELECT s3a_n.sequence, s3a_n.s, s3a_n.e, s3a_n.score, false AS reverse, true AS amino_acid, 3 AS shift_num, s3a_n.nc FROM s3a_n)
 UNION SELECT s1n_r.sequence, s1n_r.s, s1n_r.e, s1n_r.score, true AS reverse, false AS amino_acid, 1 AS shift_num, s1n_r.nc FROM s1n_r)
 UNION SELECT s1a_r.sequence, s1a_r.s, s1a_r.e, s1a_r.score, true AS reverse, true AS amino_acid, 1 AS shift_num, s1a_r.nc FROM s1a_r)
 UNION SELECT s2n_r.sequence, s2n_r.s, s2n_r.e, s2n_r.score, true AS reverse, false AS amino_acid, 2 AS shift_num, s2n_r.nc FROM s2n_r)
 UNION SELECT s2a_r.sequence, s2a_r.s, s2a_r.e, s2a_r.score, true AS reverse, true AS amino_acid, 2 AS shift_num, s2a_r.nc FROM s2a_r)
 UNION SELECT s3n_r.sequence, s3n_r.s, s3n_r.e, s3n_r.score, true AS reverse, false AS amino_acid, 3 AS shift_num, s3n_r.nc FROM s3n_r)
 UNION SELECT s3a_r.sequence, s3a_r.s, s3a_r.e, s3a_r.score, true AS reverse, true AS amino_acid, 3 AS shift_num, s3a_r.nc FROM s3a_r;
