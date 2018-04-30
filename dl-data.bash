#!/bin/bash

mkdir data/fasta/
mkdir data/annotations/

wget ftp://ftp.ensembl.org/pub/release-92/fasta/homo_sapiens/dna/README --directory-prefix=data/fasta/

wget ftp://ftp.ensembl.org/pub/release-92/fasta/homo_sapiens/dna/Homo_sapiens.GRCh38.dna.chromosome.*.fa.gz --directory-prefix=data/fasta/

wget ftp://ftp.ensembl.org/pub/grch37/release-92/gff3/homo_sapiens/Homo_sapiens.GRCh37.87.chromosome.*.gff3.gz --directory-prefix=data/annotations/


