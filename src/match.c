#include <ctype.h>
#include <stdlib.h>
#include <string.h>


typedef enum SyllableType SyllableType;
typedef struct Syllable Syllable;
typedef struct MatchState MatchState;
typedef int (*CompareFunction)(const void *a, const void *b);

enum SyllableType { Ambiguous, Prefix, Suffix };

struct Syllable {
    char text[4];
    SyllableType type;
};

struct MatchState {
    const char *remaining;
    int length;
    int score;
};

Syllable syllables[512];



int strcmp2(const void *a, const void *b) {
    return strncmp(a, b, 2);
}

int strcmp3(const void *a, const void *b) {
    return strncmp(a, b, 3);
}

Syllable *bsearch_syllables(const char *text, CompareFunction cmp) {
    return bsearch(text, syllables, 512, sizeof *syllables, cmp);
}

int type_ok(SyllableType new_type, SyllableType *type) {
    if (*type == Ambiguous) {
        if (new_type == Ambiguous)
            *type = *type == Prefix ? Suffix : Prefix;
        else
            *type = new_type;
    } else if (new_type == Ambiguous)
        *type = *type == Prefix ? Suffix : Prefix;
    else if (*type == new_type)
        return 0;
    else
        *type = new_type;
    return 1;
}

char *parse_syllable_1(char *text, SyllableType *type) {
    static SyllableType types['z' + 1] = {
        ['a'] = Prefix, ['e'] = Suffix, ['i'] = Prefix, ['o'] = Prefix,
        ['u'] = Suffix, ['y'] = Suffix,
    };
    if (strchr("jkq", *text))
        return 0;
    SyllableType new_type = types[(int) *text];
    if (!type_ok(new_type, type))
        return 0;
    return text + 1;
}

char *parse_syllable_1_initial(char *text, SyllableType *type) {
    if (!strchr("bdfhlmnprstwz", *text))
        return 0;
    if (*type == Prefix)
        *type = Suffix;
    else if (*type == Suffix)
        *type = Prefix;
    return text + 1;
}

char *parse_syllable_1_final(char *text, SyllableType *type) {
    if (!strchr("bcdfglmnprstvxz", *text))
        return 0;
    if (*type == Prefix)
        *type = Suffix;
    if (*type == Suffix)
        *type = Prefix;
    return text + 1;
}

char *parse_syllable_2_initial(char *text, SyllableType *type) {
    Syllable *syl = bsearch_syllables(text, strcmp2);
    if (!syl)
        return 0;
    if (!type_ok(syl->type, type))
        return 0;
    return text + 2;
}

char *parse_syllable_2_final(char *text, SyllableType *type) {
    for (int i = 0; i < 512; i++) {
        if (strncmp(text, syllables[i].text + 1, 2) == 0) {
            if (!type_ok(syllables[i].type, type))
                return 0;
            return text + 2;
        }
    }
    return 0;
}

char *parse_syllable_3(char *text, SyllableType *type) {
    Syllable *syl = bsearch_syllables(text, strcmp3);
    if (!(syl && type_ok(syl->type, type)))
        return 0;
    return text + 3;
}

char *valid_syllable(char *text, char *word, char *end,
                     SyllableType *type)
{
    int remaining = end - text;
    if (remaining <= 0)
        return 0;

    char *(*parse)(char *text, SyllableType *type) = 0;
    if (text == word) {
        if (remaining == 1)
            parse = parse_syllable_1;
        else if (strchr("aeiouy", *text))
            parse = parse_syllable_2_final;
        else if (strchr("aeiouy", text[1])) {
            if (remaining == 2)
                parse = parse_syllable_2_initial;
            else
                parse = parse_syllable_3;
        } else
            parse = parse_syllable_1_final;
    } else if (remaining == 1)
        parse = parse_syllable_1_initial;
    else if (remaining == 2)
        parse = parse_syllable_2_initial;
    else
        parse = parse_syllable_3;

    return parse(text, type);
}


int best_score(char *line) {
    // Lines containing non-ASCII bytes will be rejected.
    char word[strlen(line) + 1];
    for (char *r = line, *w = word;; r++) {
        if (isalpha(*r) || *r == 0)
            *w++ = tolower(*r);
        if (*r == 0) {
            *w = 0;
            break;
        }
    }
    char *text = word, *end = strchr(word, 0);
    SyllableType type = Ambiguous;
    while (text && text < end) {
        text = valid_syllable(text, word, end, &type);
        if (text == end)
            return 0;
    }
    return 1;
}


Syllable syllables[512] = {
    {"bac", Prefix}, {"bal", Prefix}, {"ban", Prefix}, {"bar", Prefix},
    {"bat", Prefix}, {"bec", Suffix}, {"bel", Suffix}, {"ben", Suffix},
    {"bep", Suffix}, {"ber", Suffix}, {"bes", Suffix}, {"bet", Suffix},
    {"bex", Suffix}, {"bic", Prefix}, {"bid", Prefix}, {"bil", Prefix},
    {"bin", Prefix}, {"bis", Prefix}, {"bit", Prefix}, {"bol", Prefix},
    {"bon", Prefix}, {"bor", Prefix}, {"bos", Prefix}, {"bot", Prefix},
    {"bud", Suffix}, {"bur", Suffix}, {"bus", Suffix}, {"byl", Suffix},
    {"byn", Suffix}, {"byr", Suffix}, {"byt", Suffix}, {"dab", Prefix},
    {"dac", Prefix}, {"dal", Prefix}, {"dan", Prefix}, {"dap", Prefix},
    {"dar", Prefix}, {"das", Prefix}, {"dat", Prefix}, {"dav", Prefix},
    {"deb", Suffix}, {"dec", Suffix}, {"def", Suffix}, {"deg", Suffix},
    {"del", Suffix}, {"dem", Suffix}, {"den", Suffix}, {"dep", Suffix},
    {"der", Suffix}, {"des", Suffix}, {"det", Suffix}, {"dev", Suffix},
    {"dex", Suffix}, {"dib", Prefix}, {"dif", Prefix}, {"dig", Prefix},
    {"dil", Prefix}, {"din", Prefix}, {"dir", Prefix}, {"dis", Prefix},
    {"div", Prefix}, {"doc", Prefix}, {"dol", Prefix}, {"don", Prefix},
    {"dop", Prefix}, {"dor", Prefix}, {"dos", Prefix}, {"dot", Prefix},
    {"dov", Prefix}, {"doz", Prefix}, {"duc", Suffix}, {"dul", Suffix},
    {"dun", Suffix}, {"dur", Suffix}, {"dus", Suffix}, {"dut", Suffix},
    {"dux", Suffix}, {"dyl", Suffix}, {"dyn", Suffix}, {"dyr", Suffix},
    {"dys", Suffix}, {"dyt", Suffix}, {"fab", Prefix}, {"fad", Prefix},
    {"fal", Prefix}, {"fam", Prefix}, {"fan", Prefix}, {"fas", Prefix},
    {"feb", Suffix}, {"fed", Suffix}, {"fel", Suffix}, {"fen", Suffix},
    {"fep", Suffix}, {"fer", Suffix}, {"fes", Suffix}, {"fet", Suffix},
    {"fex", Suffix}, {"fid", Prefix}, {"fig", Prefix}, {"fil", Prefix},
    {"fin", Prefix}, {"fip", Prefix}, {"fir", Prefix}, {"fit", Prefix},
    {"fod", Prefix}, {"fog", Prefix}, {"fol", Prefix}, {"fon", Prefix},
    {"fop", Prefix}, {"for", Prefix}, {"fos", Prefix}, {"fot", Prefix},
    {"ful", Suffix}, {"fun", Suffix}, {"fur", Suffix}, {"fus", Suffix},
    {"fyl", Suffix}, {"fyn", Suffix}, {"fyr", Suffix}, {"hab", Prefix},
    {"hac", Prefix}, {"had", Prefix}, {"hal", Prefix}, {"han", Prefix},
    {"hap", Prefix}, {"har", Prefix}, {"has", Prefix}, {"hat", Prefix},
    {"hav", Prefix}, {"heb", Suffix}, {"hec", Suffix}, {"hep", Suffix},
    {"hes", Suffix}, {"het", Suffix}, {"hex", Suffix}, {"hid", Prefix},
    {"hil", Prefix}, {"hin", Prefix}, {"hob", Prefix}, {"hoc", Prefix},
    {"hod", Prefix}, {"hol", Prefix}, {"hop", Prefix}, {"hos", Prefix},
    {"hul", Suffix}, {"hus", Suffix}, {"hut", Suffix}, {"lab", Prefix},
    {"lac", Prefix}, {"lad", Prefix}, {"lag", Prefix}, {"lan", Prefix},
    {"lap", Prefix}, {"lar", Prefix}, {"las", Prefix}, {"lat", Prefix},
    {"lav", Prefix}, {"leb", Suffix}, {"lec", Suffix}, {"led", Suffix},
    {"leg", Suffix}, {"len", Suffix}, {"lep", Suffix}, {"ler", Suffix},
    {"let", Suffix}, {"lev", Suffix}, {"lex", Suffix}, {"lib", Prefix},
    {"lid", Prefix}, {"lig", Prefix}, {"lin", Prefix}, {"lis", Prefix},
    {"lit", Prefix}, {"liv", Prefix}, {"loc", Prefix}, {"lod", Prefix},
    {"lom", Prefix}, {"lon", Prefix}, {"lop", Prefix}, {"lor", Prefix},
    {"los", Prefix}, {"luc", Suffix}, {"lud", Suffix}, {"lug", Suffix},
    {"lun", Suffix}, {"lup", Suffix}, {"lur", Suffix}, {"lus", Suffix},
    {"lut", Suffix}, {"lux", Suffix}, {"lyd", Suffix}, {"lyn", Suffix},
    {"lyr", Suffix}, {"lys", Suffix}, {"lyt", Suffix}, {"lyx", Suffix},
    {"mac", Prefix}, {"mag", Prefix}, {"mal", Prefix}, {"map", Prefix},
    {"mar", Prefix}, {"mas", Prefix}, {"mat", Prefix}, {"meb", Suffix},
    {"mec", Suffix}, {"med", Suffix}, {"meg", Suffix}, {"mel", Suffix},
    {"mep", Suffix}, {"mer", Suffix}, {"mes", Suffix}, {"met", Suffix},
    {"mev", Suffix}, {"mex", Suffix}, {"mic", Prefix}, {"mid", Prefix},
    {"mig", Prefix}, {"mil", Prefix}, {"min", Prefix}, {"mip", Prefix},
    {"mir", Prefix}, {"mis", Prefix}, {"mit", Prefix}, {"moc", Prefix},
    {"mod", Prefix}, {"mog", Prefix}, {"mol", Prefix}, {"mon", Prefix},
    {"mop", Prefix}, {"mor", Prefix}, {"mos", Prefix}, {"mot", Prefix},
    {"mud", Suffix}, {"mug", Suffix}, {"mul", Suffix}, {"mun", Suffix},
    {"mur", Suffix}, {"mus", Suffix}, {"mut", Suffix}, {"myl", Suffix},
    {"myn", Suffix}, {"myr", Suffix}, {"nac", Prefix}, {"nal", Prefix},
    {"nam", Prefix}, {"nap", Prefix}, {"nar", Prefix}, {"nat", Prefix},
    {"nav", Prefix}, {"neb", Suffix}, {"nec", Suffix}, {"ned", Suffix},
    {"nel", Suffix}, {"nem", Suffix}, {"nep", Suffix}, {"ner", Suffix},
    {"nes", Suffix}, {"net", Suffix}, {"nev", Suffix}, {"nex", Suffix},
    {"nib", Prefix}, {"nid", Prefix}, {"nil", Prefix}, {"nim", Prefix},
    {"nis", Prefix}, {"noc", Prefix}, {"nod", Prefix}, {"nol", Prefix},
    {"nom", Prefix}, {"nop", Prefix}, {"nor", Prefix}, {"nos", Prefix},
    {"nov", Prefix}, {"nub", Suffix}, {"nul", Suffix}, {"num", Suffix},
    {"nup", Suffix}, {"nus", Suffix}, {"nut", Suffix}, {"nux", Suffix},
    {"nyd", Suffix}, {"nyl", Suffix}, {"nym", Suffix}, {"nyr", Suffix},
    {"nys", Suffix}, {"nyt", Suffix}, {"nyx", Suffix}, {"pac", Prefix},
    {"pad", Prefix}, {"pag", Prefix}, {"pal", Prefix}, {"pan", Prefix},
    {"par", Prefix}, {"pas", Prefix}, {"pat", Prefix}, {"pec", Suffix},
    {"ped", Suffix}, {"peg", Suffix}, {"pel", Suffix}, {"pem", Suffix},
    {"pen", Suffix}, {"per", Suffix}, {"pes", Suffix}, {"pet", Suffix},
    {"pex", Suffix}, {"pic", Prefix}, {"pid", Prefix}, {"pil", Prefix},
    {"pin", Prefix}, {"pit", Prefix}, {"poc", Prefix}, {"pod", Prefix},
    {"pol", Prefix}, {"pon", Prefix}, {"pos", Prefix}, {"pub", Suffix},
    {"pun", Suffix}, {"pur", Suffix}, {"put", Suffix}, {"pyl", Suffix},
    {"pyx", Suffix}, {"rab", Prefix}, {"rac", Prefix}, {"rad", Prefix},
    {"rag", Prefix}, {"ral", Prefix}, {"ram", Prefix}, {"ran", Prefix},
    {"rap", Prefix}, {"rav", Prefix}, {"reb", Suffix}, {"rec", Suffix},
    {"red", Suffix}, {"ref", Suffix}, {"reg", Suffix}, {"rel", Suffix},
    {"rem", Suffix}, {"ren", Suffix}, {"rep", Suffix}, {"res", Suffix},
    {"ret", Suffix}, {"rev", Suffix}, {"rex", Suffix}, {"rib", Prefix},
    {"ric", Prefix}, {"rid", Prefix}, {"rig", Prefix}, {"ril", Prefix},
    {"rin", Prefix}, {"rip", Prefix}, {"ris", Prefix}, {"rit", Prefix},
    {"riv", Prefix}, {"roc", Prefix}, {"rol", Prefix}, {"ron", Prefix},
    {"rop", Prefix}, {"ros", Prefix}, {"rov", Prefix}, {"ruc", Suffix},
    {"rud", Suffix}, {"rul", Suffix}, {"rum", Suffix}, {"run", Suffix},
    {"rup", Suffix}, {"rus", Suffix}, {"rut", Suffix}, {"rux", Suffix},
    {"ryc", Suffix}, {"ryd", Suffix}, {"ryg", Suffix}, {"ryl", Suffix},
    {"rym", Suffix}, {"ryn", Suffix}, {"ryp", Suffix}, {"rys", Suffix},
    {"ryt", Suffix}, {"ryx", Suffix}, {"sab", Prefix}, {"sal", Prefix},
    {"sam", Prefix}, {"san", Prefix}, {"sap", Prefix}, {"sar", Prefix},
    {"sat", Prefix}, {"sav", Prefix}, {"seb", Suffix}, {"sec", Suffix},
    {"sed", Suffix}, {"sef", Suffix}, {"seg", Suffix}, {"sel", Suffix},
    {"sem", Suffix}, {"sen", Suffix}, {"sep", Suffix}, {"ser", Suffix},
    {"set", Suffix}, {"sev", Suffix}, {"sib", Prefix}, {"sic", Prefix},
    {"sid", Prefix}, {"sig", Prefix}, {"sil", Prefix}, {"sim", Prefix},
    {"sip", Prefix}, {"sit", Prefix}, {"siv", Prefix}, {"soc", Prefix},
    {"sog", Prefix}, {"sol", Prefix}, {"som", Prefix}, {"son", Prefix},
    {"sop", Prefix}, {"sor", Prefix}, {"sov", Prefix}, {"sub", Suffix},
    {"sud", Suffix}, {"sug", Suffix}, {"sul", Suffix}, {"sum", Suffix},
    {"sun", Suffix}, {"sup", Suffix}, {"sur", Suffix}, {"sut", Suffix},
    {"syd", Suffix}, {"syl", Suffix}, {"sym", Suffix}, {"syn", Suffix},
    {"syp", Suffix}, {"syr", Suffix}, {"syt", Suffix}, {"syx", Suffix},
    {"tab", Prefix}, {"tac", Prefix}, {"tad", Prefix}, {"tag", Prefix},
    {"tal", Prefix}, {"tam", Prefix}, {"tan", Prefix}, {"tap", Prefix},
    {"tar", Prefix}, {"tas", Prefix}, {"teb", Suffix}, {"tec", Suffix},
    {"ted", Suffix}, {"teg", Suffix}, {"tel", Suffix}, {"tem", Suffix},
    {"ten", Suffix}, {"tep", Suffix}, {"ter", Suffix}, {"tes", Suffix},
    {"tev", Suffix}, {"tex", Suffix}, {"tic", Prefix}, {"tid", Prefix},
    {"til", Prefix}, {"tim", Prefix}, {"tin", Prefix}, {"tip", Prefix},
    {"tir", Prefix}, {"tob", Prefix}, {"toc", Prefix}, {"tod", Prefix},
    {"tog", Prefix}, {"tol", Prefix}, {"tom", Prefix}, {"ton", Prefix},
    {"top", Prefix}, {"tor", Prefix}, {"tuc", Suffix}, {"tud", Suffix},
    {"tug", Suffix}, {"tul", Suffix}, {"tun", Suffix}, {"tus", Suffix},
    {"tux", Suffix}, {"tyc", Suffix}, {"tyd", Suffix}, {"tyl", Suffix},
    {"tyn", Suffix}, {"typ", Suffix}, {"tyr", Suffix}, {"tyv", Suffix},
    {"wac", Prefix}, {"wal", Prefix}, {"wan", Prefix}, {"wat", Prefix},
    {"web", Suffix}, {"wed", Suffix}, {"weg", Suffix}, {"wel", Suffix},
    {"wen", Suffix}, {"wep", Suffix}, {"wer", Suffix}, {"wes", Suffix},
    {"wet", Suffix}, {"wex", Suffix}, {"wic", Prefix}, {"wid", Prefix},
    {"win", Prefix}, {"wis", Prefix}, {"wit", Prefix}, {"wol", Prefix},
    {"wor", Prefix}, {"wyc", Suffix}, {"wyd", Suffix}, {"wyl", Suffix},
    {"wyn", Suffix}, {"wyt", Suffix}, {"wyx", Suffix}, {"zod", Suffix},
};

Syllable syllables_b[] = {
    {"bac", Prefix}, {"bal", Prefix}, {"ban", Prefix}, {"bar", Prefix},
    {"bat", Prefix}, {"bec", Suffix}, {"bel", Suffix}, {"ben", Suffix},
    {"bep", Suffix}, {"ber", Suffix}, {"bes", Suffix}, {"bet", Suffix},
    {"bex", Suffix}, {"bic", Prefix}, {"bid", Prefix}, {"bil", Prefix},
    {"bin", Prefix}, {"bis", Prefix}, {"bit", Prefix}, {"bol", Prefix},
    {"bon", Prefix}, {"bor", Prefix}, {"bos", Prefix}, {"bot", Prefix},
    {"bud", Suffix}, {"bur", Suffix}, {"bus", Suffix}, {"byl", Suffix},
    {"byn", Suffix}, {"byr", Suffix}, {"byt", Suffix}, {},
};

Syllable syllables_d[] = {
    {"dac", Prefix}, {"dal", Prefix}, {"dan", Prefix}, {"dap", Prefix},
    {"dar", Prefix}, {"das", Prefix}, {"dat", Prefix}, {"dav", Prefix},
    {"deb", Suffix}, {"dec", Suffix}, {"def", Suffix}, {"deg", Suffix},
    {"del", Suffix}, {"dem", Suffix}, {"den", Suffix}, {"dep", Suffix},
    {"der", Suffix}, {"des", Suffix}, {"det", Suffix}, {"dev", Suffix},
    {"dex", Suffix}, {"dib", Prefix}, {"dif", Prefix}, {"dig", Prefix},
    {"dil", Prefix}, {"din", Prefix}, {"dir", Prefix}, {"dis", Prefix},
    {"div", Prefix}, {"doc", Prefix}, {"dol", Prefix}, {"don", Prefix},
    {"dop", Prefix}, {"dor", Prefix}, {"dos", Prefix}, {"dot", Prefix},
    {"dov", Prefix}, {"doz", Prefix}, {"duc", Suffix}, {"dul", Suffix},
    {"dun", Suffix}, {"dur", Suffix}, {"dus", Suffix}, {"dut", Suffix},
    {"dux", Suffix}, {"dyl", Suffix}, {"dyn", Suffix}, {"dyr", Suffix},
    {"dys", Suffix}, {"dyt", Suffix}, {},
};

Syllable syllables_f[] = {
    {"fab", Prefix}, {"fad", Prefix}, {"fal", Prefix}, {"fam", Prefix},
    {"fan", Prefix}, {"fas", Prefix}, {"feb", Suffix}, {"fed", Suffix},
    {"fel", Suffix}, {"fen", Suffix}, {"fep", Suffix}, {"fer", Suffix},
    {"fes", Suffix}, {"fet", Suffix}, {"fex", Suffix}, {"fid", Prefix},
    {"fig", Prefix}, {"fil", Prefix}, {"fin", Prefix}, {"fip", Prefix},
    {"fir", Prefix}, {"fit", Prefix}, {"fod", Prefix}, {"fog", Prefix},
    {"fol", Prefix}, {"fon", Prefix}, {"fop", Prefix}, {"for", Prefix},
    {"fos", Prefix}, {"fot", Prefix}, {"ful", Suffix}, {"fun", Suffix},
    {"fur", Suffix}, {"fus", Suffix}, {"fyl", Suffix}, {"fyn", Suffix},
    {"fyr", Suffix}, {},
};

Syllable syllables_h[] = {
    {"hab", Prefix}, {"hac", Prefix}, {"had", Prefix}, {"hal", Prefix},
    {"han", Prefix}, {"hap", Prefix}, {"har", Prefix}, {"has", Prefix},
    {"hat", Prefix}, {"hav", Prefix}, {"heb", Suffix}, {"hec", Suffix},
    {"hep", Suffix}, {"hes", Suffix}, {"het", Suffix}, {"hex", Suffix},
    {"hid", Prefix}, {"hil", Prefix}, {"hin", Prefix}, {"hob", Prefix},
    {"hoc", Prefix}, {"hod", Prefix}, {"hol", Prefix}, {"hop", Prefix},
    {"hos", Prefix}, {"hul", Suffix}, {"hus", Suffix}, {"hut", Suffix},
    {},
};

Syllable syllables_l[] = {
    {"lab", Prefix}, {"lac", Prefix}, {"lad", Prefix}, {"lag", Prefix},
    {"lan", Prefix}, {"lap", Prefix}, {"lar", Prefix}, {"las", Prefix},
    {"lat", Prefix}, {"lav", Prefix}, {"leb", Suffix}, {"lec", Suffix},
    {"led", Suffix}, {"leg", Suffix}, {"len", Suffix}, {"lep", Suffix},
    {"ler", Suffix}, {"let", Suffix}, {"lev", Suffix}, {"lex", Suffix},
    {"lib", Prefix}, {"lid", Prefix}, {"lig", Prefix}, {"lin", Prefix},
    {"lis", Prefix}, {"lit", Prefix}, {"liv", Prefix}, {"loc", Prefix},
    {"lod", Prefix}, {"lom", Prefix}, {"lon", Prefix}, {"lop", Prefix},
    {"lor", Prefix}, {"los", Prefix}, {"luc", Suffix}, {"lud", Suffix},
    {"lug", Suffix}, {"lun", Suffix}, {"lup", Suffix}, {"lur", Suffix},
    {"lus", Suffix}, {"lut", Suffix}, {"lux", Suffix}, {"lyd", Suffix},
    {"lyn", Suffix}, {"lyr", Suffix}, {"lys", Suffix}, {"lyt", Suffix},
    {"lyx", Suffix}, {},
};

Syllable syllables_m[] = {
    {"mac", Prefix}, {"mag", Prefix}, {"mal", Prefix}, {"map", Prefix},
    {"mar", Prefix}, {"mas", Prefix}, {"mat", Prefix}, {"meb", Suffix},
    {"mec", Suffix}, {"med", Suffix}, {"meg", Suffix}, {"mel", Suffix},
    {"mep", Suffix}, {"mer", Suffix}, {"mes", Suffix}, {"met", Suffix},
    {"mev", Suffix}, {"mex", Suffix}, {"mic", Prefix}, {"mid", Prefix},
    {"mig", Prefix}, {"mil", Prefix}, {"min", Prefix}, {"mip", Prefix},
    {"mir", Prefix}, {"mis", Prefix}, {"mit", Prefix}, {"moc", Prefix},
    {"mod", Prefix}, {"mog", Prefix}, {"mol", Prefix}, {"mon", Prefix},
    {"mop", Prefix}, {"mor", Prefix}, {"mos", Prefix}, {"mot", Prefix},
    {"mud", Suffix}, {"mug", Suffix}, {"mul", Suffix}, {"mun", Suffix},
    {"mur", Suffix}, {"mus", Suffix}, {"mut", Suffix}, {"myl", Suffix},
    {"myn", Suffix}, {"myr", Suffix}, {},
};

Syllable syllables_n[] = {
    {"nac", Prefix}, {"nal", Prefix}, {"nam", Prefix}, {"nap", Prefix},
    {"nar", Prefix}, {"nat", Prefix}, {"nav", Prefix}, {"neb", Suffix},
    {"nec", Suffix}, {"ned", Suffix}, {"nel", Suffix}, {"nem", Suffix},
    {"nep", Suffix}, {"ner", Suffix}, {"nes", Suffix}, {"net", Suffix},
    {"nev", Suffix}, {"nex", Suffix}, {"nib", Prefix}, {"nid", Prefix},
    {"nil", Prefix}, {"nim", Prefix}, {"nis", Prefix}, {"noc", Prefix},
    {"nod", Prefix}, {"nol", Prefix}, {"nom", Prefix}, {"nop", Prefix},
    {"nor", Prefix}, {"nos", Prefix}, {"nov", Prefix}, {"nub", Suffix},
    {"nul", Suffix}, {"num", Suffix}, {"nup", Suffix}, {"nus", Suffix},
    {"nut", Suffix}, {"nux", Suffix}, {"nyd", Suffix}, {"nyl", Suffix},
    {"nym", Suffix}, {"nyr", Suffix}, {"nys", Suffix}, {"nyt", Suffix},
    {"nyx", Suffix}, {},
};

Syllable syllables_p[] = {
    {"pac", Prefix}, {"pad", Prefix}, {"pag", Prefix}, {"pal", Prefix},
    {"pan", Prefix}, {"par", Prefix}, {"pas", Prefix}, {"pat", Prefix},
    {"pec", Suffix}, {"ped", Suffix}, {"peg", Suffix}, {"pel", Suffix},
    {"pem", Suffix}, {"pen", Suffix}, {"per", Suffix}, {"pes", Suffix},
    {"pet", Suffix}, {"pex", Suffix}, {"pic", Prefix}, {"pid", Prefix},
    {"pil", Prefix}, {"pin", Prefix}, {"pit", Prefix}, {"poc", Prefix},
    {"pod", Prefix}, {"pol", Prefix}, {"pon", Prefix}, {"pos", Prefix},
    {"pub", Suffix}, {"pun", Suffix}, {"pur", Suffix}, {"put", Suffix},
    {"pyl", Suffix}, {"pyx", Suffix}, {},
};

Syllable syllables_r[] = {
    {"rab", Prefix}, {"rac", Prefix}, {"rad", Prefix}, {"rag", Prefix},
    {"ral", Prefix}, {"ram", Prefix}, {"ran", Prefix}, {"rap", Prefix},
    {"rav", Prefix}, {"reb", Suffix}, {"rec", Suffix}, {"red", Suffix},
    {"ref", Suffix}, {"reg", Suffix}, {"rel", Suffix}, {"rem", Suffix},
    {"ren", Suffix}, {"rep", Suffix}, {"res", Suffix}, {"ret", Suffix},
    {"rev", Suffix}, {"rex", Suffix}, {"rib", Prefix}, {"ric", Prefix},
    {"rid", Prefix}, {"rig", Prefix}, {"ril", Prefix}, {"rin", Prefix},
    {"rip", Prefix}, {"ris", Prefix}, {"rit", Prefix}, {"riv", Prefix},
    {"roc", Prefix}, {"rol", Prefix}, {"ron", Prefix}, {"rop", Prefix},
    {"ros", Prefix}, {"rov", Prefix}, {"ruc", Suffix}, {"rud", Suffix},
    {"rul", Suffix}, {"rum", Suffix}, {"run", Suffix}, {"rup", Suffix},
    {"rus", Suffix}, {"rut", Suffix}, {"rux", Suffix}, {"ryc", Suffix},
    {"ryd", Suffix}, {"ryg", Suffix}, {"ryl", Suffix}, {"rym", Suffix},
    {"ryn", Suffix}, {"ryp", Suffix}, {"rys", Suffix}, {"ryt", Suffix},
    {"ryx", Suffix}, {},
};

Syllable syllables_s[] = {
    {"sab", Prefix}, {"sal", Prefix}, {"sam", Prefix}, {"san", Prefix},
    {"sap", Prefix}, {"sar", Prefix}, {"sat", Prefix}, {"sav", Prefix},
    {"seb", Suffix}, {"sec", Suffix}, {"sed", Suffix}, {"sef", Suffix},
    {"seg", Suffix}, {"sel", Suffix}, {"sem", Suffix}, {"sen", Suffix},
    {"sep", Suffix}, {"ser", Suffix}, {"set", Suffix}, {"sev", Suffix},
    {"sib", Prefix}, {"sic", Prefix}, {"sid", Prefix}, {"sig", Prefix},
    {"sil", Prefix}, {"sim", Prefix}, {"sip", Prefix}, {"sit", Prefix},
    {"siv", Prefix}, {"soc", Prefix}, {"sog", Prefix}, {"sol", Prefix},
    {"som", Prefix}, {"son", Prefix}, {"sop", Prefix}, {"sor", Prefix},
    {"sov", Prefix}, {"sub", Suffix}, {"sud", Suffix}, {"sug", Suffix},
    {"sul", Suffix}, {"sum", Suffix}, {"sun", Suffix}, {"sup", Suffix},
    {"sur", Suffix}, {"sut", Suffix}, {"syd", Suffix}, {"syl", Suffix},
    {"sym", Suffix}, {"syn", Suffix}, {"syp", Suffix}, {"syr", Suffix},
    {"syt", Suffix}, {"syx", Suffix}, {},
};

Syllable syllables_t[] = {
    {"tab", Prefix}, {"tac", Prefix}, {"tad", Prefix}, {"tag", Prefix},
    {"tal", Prefix}, {"tam", Prefix}, {"tan", Prefix}, {"tap", Prefix},
    {"tar", Prefix}, {"tas", Prefix}, {"teb", Suffix}, {"tec", Suffix},
    {"ted", Suffix}, {"teg", Suffix}, {"tel", Suffix}, {"tem", Suffix},
    {"ten", Suffix}, {"tep", Suffix}, {"ter", Suffix}, {"tes", Suffix},
    {"tev", Suffix}, {"tex", Suffix}, {"tic", Prefix}, {"tid", Prefix},
    {"til", Prefix}, {"tim", Prefix}, {"tin", Prefix}, {"tip", Prefix},
    {"tir", Prefix}, {"tob", Prefix}, {"toc", Prefix}, {"tod", Prefix},
    {"tog", Prefix}, {"tol", Prefix}, {"tom", Prefix}, {"ton", Prefix},
    {"top", Prefix}, {"tor", Prefix}, {"tuc", Suffix}, {"tud", Suffix},
    {"tug", Suffix}, {"tul", Suffix}, {"tun", Suffix}, {"tus", Suffix},
    {"tux", Suffix}, {"tyc", Suffix}, {"tyd", Suffix}, {"tyl", Suffix},
    {"tyn", Suffix}, {"typ", Suffix}, {"tyr", Suffix}, {"tyv", Suffix},
    {},
};

Syllable syllables_w[] = {
    {"wac", Prefix}, {"wal", Prefix}, {"wan", Prefix}, {"wat", Prefix},
    {"web", Suffix}, {"wed", Suffix}, {"weg", Suffix}, {"wel", Suffix},
    {"wen", Suffix}, {"wep", Suffix}, {"wer", Suffix}, {"wes", Suffix},
    {"wet", Suffix}, {"wex", Suffix}, {"wic", Prefix}, {"wid", Prefix},
    {"win", Prefix}, {"wis", Prefix}, {"wit", Prefix}, {"wol", Prefix},
    {"wor", Prefix}, {"wyc", Suffix}, {"wyd", Suffix}, {"wyl", Suffix},
    {"wyn", Suffix}, {"wyt", Suffix}, {"wyx", Suffix}, {},
};

Syllable syllables_z[] = {
    {"zod", Suffix}, {}
};

Syllable *syllable_groups[] = {
    syllables_b, syllables_d, syllables_f, syllables_h, syllables_l,
    syllables_m, syllables_n, syllables_p, syllables_r, syllables_s,
    syllables_t, syllables_w, syllables_z, 0
};
