#ifndef PLINK_BIN
#define PLINK_BIN

#include <string>
#include <vector>
#include <map>
#include <set>
#include <fcntl.h>
#include <sys/mman.h>
#include "snp.h"
#include "individual.h"
#include "exceptions.h"

class plink_binary
{
    friend class plink_utils;

private:
    bool open_for_write;
    std::fstream *bed_file;

    // for bed file
    bool is_mem_mapped;
    char *fmap;
    size_t flen;
    int fd;
    unsigned int snp_ptr;      // index to next snp to be read
    unsigned int bytes_per_snp;

    void read_bed_header();

    void write_bed_header();

    void bed_write(gftools::snp s, std::vector<int> genotypes);

    void uncompress_calls(char *buffer, size_t len, std::vector<int> &genotypes);

    void compress_calls(char *buffer, std::vector<int> genotypes);

    void open_bed_write(std::string filename);

    void open_bed_read(std::string filename, bool quell_mem_mapping);

    void get_snp(size_t pos, std::vector<int> &genotypes);

    void extract_bed(size_t pos, size_t len, char *buffer);

    void init(std::string dataset, bool mode);

public:
    std::string dataset;
    char missing_genotype;
    bool quell_mem_mapping;
    void open(std::string dataset, bool mode);

    void open(std::string dataset);

    plink_binary(std::string dataset);
    plink_binary();
    ~plink_binary();
    void close(void);

    // bim and fam file parsing functions
    // public in case they might be useful to someone
    void read_bim(std::vector<gftools::snp> &snps);

    void write_bim(std::vector<gftools::snp> snps);

    gftools::snp from_bim(std::string record);

    std::string to_bim(gftools::snp snp);

    void read_fam(std::vector<gftools::individual> &ind);

    void write_fam(std::vector<gftools::individual> ind);

    gftools::individual from_fam(std::string record);

    std::string to_fam(gftools::individual ind);

    std::vector<gftools::snp> snps;
    std::vector<gftools::individual> individuals;
    std::map<std::string, int> snp_index;

    bool next_snp(gftools::snp &s, std::vector<std::string> &genotypes);

    void read_snp(std::string snp, std::vector<std::string> &genotypes);

    void read_snp(int snp, std::vector<int> &genotypes);

    void write_snp(gftools::snp s, std::vector<int> genotypes);

    void write_snp(gftools::snp s, std::vector<std::string> genotypes);

    void genotypes_itoa(gftools::snp s, std::vector<int> g_num, std::vector<std::string> &g_str);

    void genotypes_atoi(gftools::snp &s, std::vector<std::string> g_str, std::vector<int> &g_num);

};

#endif // PLINK_BIN