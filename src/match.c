#include <ctype.h>
#include <stdlib.h>
#include <string.h>


typedef struct Syllable Syllable;

struct Syllable {
    char text[4];
    char is_suffix;
};

Syllable syllables[512];


int strcmp2(const void *a, const void *b) {
    return strncmp(a, b, 2);
}

int strcmp3(const void *a, const void *b) {
    return strncmp(a, b, 3);
}

Syllable *find_syllable(const char *text) {
    return bsearch(text, syllables, 512, sizeof *syllables, strcmp3);
}

Syllable *find_syllable_2(const char *text) {
    return bsearch(text, syllables, 512, sizeof *syllables, strcmp2);
}

Syllable *find_syllable_2_final(const char *text) {
    for (int i = 0; i < 512; i++) {
        if (strncmp(text + 1, syllables[i].text + 1, 2) == 0)
            return syllables + i;
    }
    return 0;
}

int valid_syllable(const char **scanner, const char *word,
                   const char *end, int *direction)
{
    Syllable *(*search)(const char *text);
    if (*scanner == word && *scanner + 1 < end &&
        strchr("aeiouy", word[0]))
    {
        --*scanner;
        search = find_syllable_2_final;
    } else
        switch (end - *scanner) {
        case 0:
            return 0;
        case 1:
            if (*scanner == word)
                return ++*scanner, !strchr("jkq", *word);
            if (**scanner == 'z' && !*direction)
                return ++*scanner, 0;
            *direction = !*direction;
            return !strchr("acegijkoquvy", *(*scanner)++);
        case 2:
            search = find_syllable_2;
            break;
        default:
            search = find_syllable;
        }
    Syllable *syl = search(*scanner);
    if (syl == 0)
        return 0;
    *scanner += 3;
    *direction = syl->is_suffix;
    return 1;
}


int valid_word(char *line) {
    char word[strlen(line) + 1];
    for (char *r = line, *w = word;; r++) {
        if (isalpha(*r) || *r == 0)
            *w++ = tolower(*r);
        if (*r < 0)
            return 0;
        if (*r == 0)
            break;
    }
    char *scanner = word, *end = strchr(word, 0);
    int direction = -1;
    while (*scanner != 0) {
        int prev_direction = direction;
        if (!valid_syllable((const char**) &scanner, word, end, &direction))
            return 0;
        if (direction == prev_direction && prev_direction != -1)
            return 0;
    }
    return 1;
}


Syllable syllables[512] = {
    {"bac", 0}, {"bal", 0}, {"ban", 0}, {"bar", 0},
    {"bat", 0}, {"bec", 1}, {"bel", 1}, {"ben", 1},
    {"bep", 1}, {"ber", 1}, {"bes", 1}, {"bet", 1},
    {"bex", 1}, {"bic", 0}, {"bid", 0}, {"bil", 0},
    {"bin", 0}, {"bis", 0}, {"bit", 0}, {"bol", 0},
    {"bon", 0}, {"bor", 0}, {"bos", 0}, {"bot", 0},
    {"bud", 1}, {"bur", 1}, {"bus", 1}, {"byl", 1},
    {"byn", 1}, {"byr", 1}, {"byt", 1}, {"dab", 0},
    {"dac", 0}, {"dal", 0}, {"dan", 0}, {"dap", 0},
    {"dar", 0}, {"das", 0}, {"dat", 0}, {"dav", 0},
    {"deb", 1}, {"dec", 1}, {"def", 1}, {"deg", 1},
    {"del", 1}, {"dem", 1}, {"den", 1}, {"dep", 1},
    {"der", 1}, {"des", 1}, {"det", 1}, {"dev", 1},
    {"dex", 1}, {"dib", 0}, {"dif", 0}, {"dig", 0},
    {"dil", 0}, {"din", 0}, {"dir", 0}, {"dis", 0},
    {"div", 0}, {"doc", 0}, {"dol", 0}, {"don", 0},
    {"dop", 0}, {"dor", 0}, {"dos", 0}, {"dot", 0},
    {"dov", 0}, {"doz", 0}, {"duc", 1}, {"dul", 1},
    {"dun", 1}, {"dur", 1}, {"dus", 1}, {"dut", 1},
    {"dux", 1}, {"dyl", 1}, {"dyn", 1}, {"dyr", 1},
    {"dys", 1}, {"dyt", 1}, {"fab", 0}, {"fad", 0},
    {"fal", 0}, {"fam", 0}, {"fan", 0}, {"fas", 0},
    {"feb", 1}, {"fed", 1}, {"fel", 1}, {"fen", 1},
    {"fep", 1}, {"fer", 1}, {"fes", 1}, {"fet", 1},
    {"fex", 1}, {"fid", 0}, {"fig", 0}, {"fil", 0},
    {"fin", 0}, {"fip", 0}, {"fir", 0}, {"fit", 0},
    {"fod", 0}, {"fog", 0}, {"fol", 0}, {"fon", 0},
    {"fop", 0}, {"for", 0}, {"fos", 0}, {"fot", 0},
    {"ful", 1}, {"fun", 1}, {"fur", 1}, {"fus", 1},
    {"fyl", 1}, {"fyn", 1}, {"fyr", 1}, {"hab", 0},
    {"hac", 0}, {"had", 0}, {"hal", 0}, {"han", 0},
    {"hap", 0}, {"har", 0}, {"has", 0}, {"hat", 0},
    {"hav", 0}, {"heb", 1}, {"hec", 1}, {"hep", 1},
    {"hes", 1}, {"het", 1}, {"hex", 1}, {"hid", 0},
    {"hil", 0}, {"hin", 0}, {"hob", 0}, {"hoc", 0},
    {"hod", 0}, {"hol", 0}, {"hop", 0}, {"hos", 0},
    {"hul", 1}, {"hus", 1}, {"hut", 1}, {"lab", 0},
    {"lac", 0}, {"lad", 0}, {"lag", 0}, {"lan", 0},
    {"lap", 0}, {"lar", 0}, {"las", 0}, {"lat", 0},
    {"lav", 0}, {"leb", 1}, {"lec", 1}, {"led", 1},
    {"leg", 1}, {"len", 1}, {"lep", 1}, {"ler", 1},
    {"let", 1}, {"lev", 1}, {"lex", 1}, {"lib", 0},
    {"lid", 0}, {"lig", 0}, {"lin", 0}, {"lis", 0},
    {"lit", 0}, {"liv", 0}, {"loc", 0}, {"lod", 0},
    {"lom", 0}, {"lon", 0}, {"lop", 0}, {"lor", 0},
    {"los", 0}, {"luc", 1}, {"lud", 1}, {"lug", 1},
    {"lun", 1}, {"lup", 1}, {"lur", 1}, {"lus", 1},
    {"lut", 1}, {"lux", 1}, {"lyd", 1}, {"lyn", 1},
    {"lyr", 1}, {"lys", 1}, {"lyt", 1}, {"lyx", 1},
    {"mac", 0}, {"mag", 0}, {"mal", 0}, {"map", 0},
    {"mar", 0}, {"mas", 0}, {"mat", 0}, {"meb", 1},
    {"mec", 1}, {"med", 1}, {"meg", 1}, {"mel", 1},
    {"mep", 1}, {"mer", 1}, {"mes", 1}, {"met", 1},
    {"mev", 1}, {"mex", 1}, {"mic", 0}, {"mid", 0},
    {"mig", 0}, {"mil", 0}, {"min", 0}, {"mip", 0},
    {"mir", 0}, {"mis", 0}, {"mit", 0}, {"moc", 0},
    {"mod", 0}, {"mog", 0}, {"mol", 0}, {"mon", 0},
    {"mop", 0}, {"mor", 0}, {"mos", 0}, {"mot", 0},
    {"mud", 1}, {"mug", 1}, {"mul", 1}, {"mun", 1},
    {"mur", 1}, {"mus", 1}, {"mut", 1}, {"myl", 1},
    {"myn", 1}, {"myr", 1}, {"nac", 0}, {"nal", 0},
    {"nam", 0}, {"nap", 0}, {"nar", 0}, {"nat", 0},
    {"nav", 0}, {"neb", 1}, {"nec", 1}, {"ned", 1},
    {"nel", 1}, {"nem", 1}, {"nep", 1}, {"ner", 1},
    {"nes", 1}, {"net", 1}, {"nev", 1}, {"nex", 1},
    {"nib", 0}, {"nid", 0}, {"nil", 0}, {"nim", 0},
    {"nis", 0}, {"noc", 0}, {"nod", 0}, {"nol", 0},
    {"nom", 0}, {"nop", 0}, {"nor", 0}, {"nos", 0},
    {"nov", 0}, {"nub", 1}, {"nul", 1}, {"num", 1},
    {"nup", 1}, {"nus", 1}, {"nut", 1}, {"nux", 1},
    {"nyd", 1}, {"nyl", 1}, {"nym", 1}, {"nyr", 1},
    {"nys", 1}, {"nyt", 1}, {"nyx", 1}, {"pac", 0},
    {"pad", 0}, {"pag", 0}, {"pal", 0}, {"pan", 0},
    {"par", 0}, {"pas", 0}, {"pat", 0}, {"pec", 1},
    {"ped", 1}, {"peg", 1}, {"pel", 1}, {"pem", 1},
    {"pen", 1}, {"per", 1}, {"pes", 1}, {"pet", 1},
    {"pex", 1}, {"pic", 0}, {"pid", 0}, {"pil", 0},
    {"pin", 0}, {"pit", 0}, {"poc", 0}, {"pod", 0},
    {"pol", 0}, {"pon", 0}, {"pos", 0}, {"pub", 1},
    {"pun", 1}, {"pur", 1}, {"put", 1}, {"pyl", 1},
    {"pyx", 1}, {"rab", 0}, {"rac", 0}, {"rad", 0},
    {"rag", 0}, {"ral", 0}, {"ram", 0}, {"ran", 0},
    {"rap", 0}, {"rav", 0}, {"reb", 1}, {"rec", 1},
    {"red", 1}, {"ref", 1}, {"reg", 1}, {"rel", 1},
    {"rem", 1}, {"ren", 1}, {"rep", 1}, {"res", 1},
    {"ret", 1}, {"rev", 1}, {"rex", 1}, {"rib", 0},
    {"ric", 0}, {"rid", 0}, {"rig", 0}, {"ril", 0},
    {"rin", 0}, {"rip", 0}, {"ris", 0}, {"rit", 0},
    {"riv", 0}, {"roc", 0}, {"rol", 0}, {"ron", 0},
    {"rop", 0}, {"ros", 0}, {"rov", 0}, {"ruc", 1},
    {"rud", 1}, {"rul", 1}, {"rum", 1}, {"run", 1},
    {"rup", 1}, {"rus", 1}, {"rut", 1}, {"rux", 1},
    {"ryc", 1}, {"ryd", 1}, {"ryg", 1}, {"ryl", 1},
    {"rym", 1}, {"ryn", 1}, {"ryp", 1}, {"rys", 1},
    {"ryt", 1}, {"ryx", 1}, {"sab", 0}, {"sal", 0},
    {"sam", 0}, {"san", 0}, {"sap", 0}, {"sar", 0},
    {"sat", 0}, {"sav", 0}, {"seb", 1}, {"sec", 1},
    {"sed", 1}, {"sef", 1}, {"seg", 1}, {"sel", 1},
    {"sem", 1}, {"sen", 1}, {"sep", 1}, {"ser", 1},
    {"set", 1}, {"sev", 1}, {"sib", 0}, {"sic", 0},
    {"sid", 0}, {"sig", 0}, {"sil", 0}, {"sim", 0},
    {"sip", 0}, {"sit", 0}, {"siv", 0}, {"soc", 0},
    {"sog", 0}, {"sol", 0}, {"som", 0}, {"son", 0},
    {"sop", 0}, {"sor", 0}, {"sov", 0}, {"sub", 1},
    {"sud", 1}, {"sug", 1}, {"sul", 1}, {"sum", 1},
    {"sun", 1}, {"sup", 1}, {"sur", 1}, {"sut", 1},
    {"syd", 1}, {"syl", 1}, {"sym", 1}, {"syn", 1},
    {"syp", 1}, {"syr", 1}, {"syt", 1}, {"syx", 1},
    {"tab", 0}, {"tac", 0}, {"tad", 0}, {"tag", 0},
    {"tal", 0}, {"tam", 0}, {"tan", 0}, {"tap", 0},
    {"tar", 0}, {"tas", 0}, {"teb", 1}, {"tec", 1},
    {"ted", 1}, {"teg", 1}, {"tel", 1}, {"tem", 1},
    {"ten", 1}, {"tep", 1}, {"ter", 1}, {"tes", 1},
    {"tev", 1}, {"tex", 1}, {"tic", 0}, {"tid", 0},
    {"til", 0}, {"tim", 0}, {"tin", 0}, {"tip", 0},
    {"tir", 0}, {"tob", 0}, {"toc", 0}, {"tod", 0},
    {"tog", 0}, {"tol", 0}, {"tom", 0}, {"ton", 0},
    {"top", 0}, {"tor", 0}, {"tuc", 1}, {"tud", 1},
    {"tug", 1}, {"tul", 1}, {"tun", 1}, {"tus", 1},
    {"tux", 1}, {"tyc", 1}, {"tyd", 1}, {"tyl", 1},
    {"tyn", 1}, {"typ", 1}, {"tyr", 1}, {"tyv", 1},
    {"wac", 0}, {"wal", 0}, {"wan", 0}, {"wat", 0},
    {"web", 1}, {"wed", 1}, {"weg", 1}, {"wel", 1},
    {"wen", 1}, {"wep", 1}, {"wer", 1}, {"wes", 1},
    {"wet", 1}, {"wex", 1}, {"wic", 0}, {"wid", 0},
    {"win", 0}, {"wis", 0}, {"wit", 0}, {"wol", 0},
    {"wor", 0}, {"wyc", 1}, {"wyd", 1}, {"wyl", 1},
    {"wyn", 1}, {"wyt", 1}, {"wyx", 1}, {"zod", 1},
};
