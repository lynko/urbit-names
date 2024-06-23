#include <assert.h>
#include <stdio.h>
#include <string.h>


typedef struct BatteryStats BatteryStats;

struct BatteryStats {
    int total;
    int passed;
    int failed;
};


BatteryStats total, batteries, this_battery;
const char *battery_name;


void test(const char *text, int result, const char *file, int line);

void begin_battery(const char *name);
void end_battery();
void report_battery(const char *msg, BatteryStats *stats);
int tests_done();

void test_one_letter();
void test_two_letters();
void test_literal_syllables();
void test_affix_pattern();
void test_affix_pattern_initial_vowel();

int main() {
    test_one_letter();
    test_two_letters();
    test_literal_syllables();
    test_affix_pattern();
    test_affix_pattern_initial_vowel();
    return tests_done();
}


#define Apply(x, ...) x(__VA_ARGS__)
#define Test(condition) test(#condition, condition, __FILE__, __LINE__)
#define TestExact(word) Apply(Test, best_score(word) == 0)
#define TestInexact(word) Apply(Test, best_score(word) != 0)

// Note: this doesn't correctly handle non-printing characters.
//
#define TestExactAll(...) do {                                       \
    const char *words[] = { __VA_ARGS__ };                           \
    for (int i = 0; i < (int) (sizeof words / sizeof *words); i++) { \
        char buffer[64] = "best_score(\"";                           \
        assert(strlen(words[i]) <= sizeof buffer - 20);              \
        strcat(buffer, words[i]);                                    \
        strcat(buffer, "\") == 0");                                  \
        test(buffer, best_score(words[i]) == 0, __FILE__, __LINE__); \
    }                                                                \
} while (0)

// Note: this doesn't correctly handle non-printing characters.
//
#define TestInexactAll(...) do {                                     \
    const char *words[] = { __VA_ARGS__ };                           \
    for (int i = 0; i < (int) (sizeof words / sizeof *words); i++) { \
        char buffer[64] = "best_score(\"";                           \
        assert(strlen(words[i]) <= sizeof buffer - 20);              \
        strcat(buffer, words[i]);                                    \
        strcat(buffer, "\") != 0");                                  \
        test(buffer, best_score(words[i]) != 0, __FILE__, __LINE__); \
    }                                                                \
} while (0)

int best_score(const char *line);

void test_one_letter() {
    begin_battery("Test one letter");
    TestExactAll("a", "b", "c", "d", "e", "f", "g", "h", "i", "l", "m",
                 "n", "o", "p", "r", "s", "t", "u", "v", "w", "x", "y",
                 "z");
    TestInexactAll("j", "k", "q");
}

void test_two_letters() {
    begin_battery("Test two letters");
    TestExactAll("ab", "ac", "ad", "ag", "al", "am", "an", "ap", "ar",
                 "as", "at", "av");
    TestInexactAll("aa", "ae", "af", "ah", "ai", "aj", "ak", "ao", "aq",
                   "au", "aw", "ax", "ay", "az");
    TestExactAll("ba", "bb", "bd", "be", "bf", "bh", "bi", "bl", "bm",
                 "bn", "bo", "bp", "br", "bs", "bt", "bu", "bw", "by",
                 "bz");
    TestInexactAll("bc", "bg", "bj", "bk", "bq", "bv", "bx");
    TestExactAll("cb", "cd", "cf", "ch", "cl", "cm", "cn", "cp", "cr",
                 "cs", "ct", "cw", "cz");
    TestInexactAll("ca", "cc", "ce", "cg", "ci", "cj", "ck", "co", "cq",
                   "cu", "cv", "cx", "cy");
    TestExactAll("da", "db", "dd", "de", "df", "dh", "di", "dl", "dm",
                 "dn", "do", "dp", "dr", "ds", "dt", "du", "dw", "dy",
                 "dz");
    TestInexactAll("dc", "dg", "dj", "dk", "dq", "dv", "dx");
    TestExactAll("eb", "ec", "ed", "ef", "eg", "el", "em", "en", "ep",
                 "er", "es", "et", "ev", "ex");
    TestInexactAll("ea", "ee", "eh", "ei", "ej", "ek", "eo", "eq", "eu",
                   "ew", "ey", "ez");
    TestExactAll("fa", "fb", "fd", "fe", "ff", "fh", "fi", "fl", "fm",
                 "fn", "fo", "fp", "fr", "fs", "ft", "fu", "fw", "fy",
                 "fz");
    TestInexactAll("fc", "fg", "fj", "fk", "fq", "fv", "fx");
    TestExactAll("gb", "gd", "gf", "gh", "gl", "gm", "gn", "gp", "gr",
                 "gs", "gt", "gw", "gz");
    TestInexactAll("ga", "gc", "ge", "gg", "gi", "gj", "gk", "go", "gq",
                   "gu", "gv", "gx", "gy");
    TestExactAll("ha", "he", "hi", "ho", "hu");
    TestInexactAll("hb", "hc", "hd", "hf", "hg", "hh", "hj", "hk", "hl",
                   "hm", "hn", "hp", "hq", "hr", "hs", "ht", "hv",
                   "hw", "hx", "hy", "hz");
    TestExactAll("ib", "ic", "id", "if", "ig", "il", "im", "in", "ip",
                 "ir", "is", "it", "iv");
    TestInexactAll("ia", "ie", "ih", "ii", "ij", "ik", "io", "iq", "iu",
                   "iw", "ix", "iy", "iz");
    TestInexactAll("ja", "jb", "jc", "jd", "je", "jf", "jg", "jh", "ji",
                   "jj", "jk", "jl", "jm", "jn", "jo", "jp", "jq", "jr",
                   "js", "jt", "ju", "jv", "jw", "jx", "jy", "jz");
    TestInexactAll("ka", "kb", "kc", "kd", "ke", "kf", "kg", "kh", "ki",
                   "kj", "kk", "kl", "km", "kn", "ko", "kp", "kq", "kr",
                   "ks", "kt", "ku", "kv", "kw", "kx", "ky", "kz");
    TestExactAll("la", "lb", "ld", "le", "lf", "lh", "li", "ll", "lm",
                 "ln", "lo", "lp", "lr", "ls", "lt", "lu", "lw", "ly",
                 "lz");
    TestInexactAll("lc", "lg", "lj", "lk", "lq", "lv", "lx");
    TestExactAll("ma", "mb", "md", "me", "mf", "mh", "mi", "ml", "mm",
                 "mn", "mo", "mp", "mr", "ms", "mt", "mu", "mw", "my",
                 "mz");
    TestInexactAll("mc", "mg", "mj", "mk", "mq", "mv", "mx");
    TestExactAll("na", "nb", "nd", "ne", "nf", "nh", "ni", "nl", "nm",
                 "nn", "no", "np", "nr", "ns", "nt", "nu", "nw", "ny",
                 "nz");
    TestInexactAll("nc", "ng", "nj", "nk", "nq", "nv", "nx");
    TestExactAll("ob", "oc", "od", "og", "ol", "om", "on", "op", "or",
                 "os", "ot", "ov", "oz");
    TestInexactAll("oa", "oe", "of", "oh", "oi", "oj", "ok", "oo", "oq",
                   "ou", "ow", "ox", "oy");
    TestExactAll("pa", "pb", "pd", "pe", "pf", "ph", "pi", "pl", "pm",
                 "pn", "po", "pp", "pr", "ps", "pt", "pu", "pw", "py",
                 "pz");
    TestInexactAll("pc", "pg", "pj", "pk", "pq", "pv", "px");
    TestInexactAll("qa", "qb", "qc", "qd", "qe", "qf", "qg", "qh", "qi",
                   "qj", "qk", "ql", "qm", "qn", "qo", "qp", "qq", "qr",
                   "qs", "qt", "qu", "qv", "qw", "qx", "qy", "qz");
    TestExactAll("ra", "rb", "rd", "re", "rf", "rh", "ri", "rl", "rm",
                 "rn", "ro", "rp", "rr", "rs", "rt", "ru", "rw", "ry",
                 "rz");
    TestInexactAll("rc", "rg", "rj", "rk", "rq", "rv", "rx");
    TestExactAll("sa", "sb", "sd", "se", "sf", "sh", "si", "sl", "sm",
                 "sn", "so", "sp", "sr", "ss", "st", "su", "sw", "sy",
                 "sz");
    TestInexactAll("sc", "sg", "sj", "sk", "sq", "sv", "sx");
    TestExactAll("ta", "tb", "td", "te", "tf", "th", "ti", "tl", "tm",
                 "tn", "to", "tp", "tr", "ts", "tt", "tu", "tw", "ty",
                 "tz");
    TestInexactAll("tc", "tg", "tj", "tk", "tq", "tv", "tx");
    TestExactAll("ub", "uc", "ud", "ug", "ul", "um", "un", "up", "ur",
                 "us", "ut", "ux");
    TestInexactAll("ua", "ue", "uf", "uh", "ui", "uj", "uk", "uo", "uq",
                   "uu", "uv", "uw", "uy", "uz");
    TestExactAll("vb", "vd", "vf", "vh", "vl", "vm", "vn", "vp", "vr",
                 "vs", "vt", "vw", "vz");
    TestInexactAll("va", "vc", "ve", "vi", "vg", "vj", "vk", "vo", "vq",
                   "vu", "vv", "vx", "vy");
    TestExactAll("wa", "we", "wi", "wo", "wy");
    TestInexactAll("wb", "wc", "wd", "wf", "wg", "wh", "wj", "wk", "wl",
                   "wm", "wn", "wp", "wq", "wr", "ws", "wt", "wu", "wv",
                   "ww", "wx", "wz");
    TestExactAll("xb", "xd", "xf", "xh", "xl", "xm", "xn", "xp", "xr",
                 "xs", "xt", "xw", "xz");
    TestInexactAll("xa", "xc", "xe", "xi", "xg", "xj", "xk", "xo", "xq",
                   "xu", "xv", "xx", "xy");
    TestExactAll("yc", "yd", "yg", "yl", "ym", "yn", "yp", "yr", "ys",
                 "yt", "yv", "yx");
    TestInexactAll("ya", "yb", "ye", "yf", "yh", "yi", "yj", "yk", "yo",
                   "yq", "yu", "yw", "yy", "yz");
    TestExactAll("zb", "zd", "zf", "zh", "zl", "zm", "zn", "zo", "zp",
                 "zr", "zs", "zt", "zw", "zz");
    TestInexactAll("za", "zc", "ze", "zg", "zi", "zj", "zk", "zq", "zu",
                   "zv", "zx", "zy");
    Test(this_battery.total == 26 * 26);
}

void test_literal_syllables() {
    begin_battery("Test literal syllables");
    TestExactAll(
        "bac", "bal", "ban", "bar", "bat", "bec", "bel", "ben", "bep",
        "ber", "bes", "bet", "bex", "bic", "bid", "bil", "bin", "bis",
        "bit", "bol", "bon", "bor", "bos", "bot", "bud", "bur", "bus",
        "byl", "byn", "byr", "byt", "dab", "dac", "dal", "dan", "dap",
        "dar", "das", "dat", "dav", "deb", "dec", "def", "deg", "del",
        "dem", "den", "dep", "der", "des", "det", "dev", "dex", "dib",
        "dif", "dig", "dil", "din", "dir", "dis", "div", "doc", "dol",
        "don", "dop", "dor", "dos", "dot", "dov", "doz", "duc", "dul",
        "dun", "dur", "dus", "dut", "dux", "dyl", "dyn", "dyr", "dys",
        "dyt", "fab", "fad", "fal", "fam", "fan", "fas", "feb", "fed",
        "fel", "fen", "fep", "fer", "fes", "fet", "fex", "fid", "fig",
        "fil", "fin", "fip", "fir", "fit", "fod", "fog", "fol", "fon",
        "fop", "for", "fos", "fot", "ful", "fun", "fur", "fus", "fyl",
        "fyn", "fyr", "hab", "hac", "had", "hal", "han", "hap", "har",
        "has", "hat", "hav", "heb", "hec", "hep", "hes", "het", "hex",
        "hid", "hil", "hin", "hob", "hoc", "hod", "hol", "hop", "hos",
        "hul", "hus", "hut", "lab", "lac", "lad", "lag", "lan", "lap",
        "lar", "las", "lat", "lav", "leb", "lec", "led", "leg", "len",
        "lep", "ler", "let", "lev", "lex", "lib", "lid", "lig", "lin",
        "lis", "lit", "liv", "loc", "lod", "lom", "lon", "lop", "lor",
        "los", "luc", "lud", "lug", "lun", "lup", "lur", "lus", "lut",
        "lux", "lyd", "lyn", "lyr", "lys", "lyt", "lyx", "mac", "mag",
        "mal", "map", "mar", "mas", "mat", "meb", "mec", "med", "meg",
        "mel", "mep", "mer", "mes", "met", "mev", "mex", "mic", "mid",
        "mig", "mil", "min", "mip", "mir", "mis", "mit", "moc", "mod",
        "mog", "mol", "mon", "mop", "mor", "mos", "mot", "mud", "mug",
        "mul", "mun", "mur", "mus", "mut", "myl", "myn", "myr", "nac",
        "nal", "nam", "nap", "nar", "nat", "nav", "neb", "nec", "ned",
        "nel", "nem", "nep", "ner", "nes", "net", "nev", "nex", "nib",
        "nid", "nil", "nim", "nis", "noc", "nod", "nol", "nom", "nop",
        "nor", "nos", "nov", "nub", "nul", "num", "nup", "nus", "nut",
        "nux", "nyd", "nyl", "nym", "nyr", "nys", "nyt", "nyx", "pac",
        "pad", "pag", "pal", "pan", "par", "pas", "pat", "pec", "ped",
        "peg", "pel", "pem", "pen", "per", "pes", "pet", "pex", "pic",
        "pid", "pil", "pin", "pit", "poc", "pod", "pol", "pon", "pos",
        "pub", "pun", "pur", "put", "pyl", "pyx", "rab", "rac", "rad",
        "rag", "ral", "ram", "ran", "rap", "rav", "reb", "rec", "red",
        "ref", "reg", "rel", "rem", "ren", "rep", "res", "ret", "rev",
        "rex", "rib", "ric", "rid", "rig", "ril", "rin", "rip", "ris",
        "rit", "riv", "roc", "rol", "ron", "rop", "ros", "rov", "ruc",
        "rud", "rul", "rum", "run", "rup", "rus", "rut", "rux", "ryc",
        "ryd", "ryg", "ryl", "rym", "ryn", "ryp", "rys", "ryt", "ryx",
        "sab", "sal", "sam", "san", "sap", "sar", "sat", "sav", "seb",
        "sec", "sed", "sef", "seg", "sel", "sem", "sen", "sep", "ser",
        "set", "sev", "sib", "sic", "sid", "sig", "sil", "sim", "sip",
        "sit", "siv", "soc", "sog", "sol", "som", "son", "sop", "sor",
        "sov", "sub", "sud", "sug", "sul", "sum", "sun", "sup", "sur",
        "sut", "syd", "syl", "sym", "syn", "syp", "syr", "syt", "syx",
        "tab", "tac", "tad", "tag", "tal", "tam", "tan", "tap", "tar",
        "tas", "teb", "tec", "ted", "teg", "tel", "tem", "ten", "tep",
        "ter", "tes", "tev", "tex", "tic", "tid", "til", "tim", "tin",
        "tip", "tir", "tob", "toc", "tod", "tog", "tol", "tom", "ton",
        "top", "tor", "tuc", "tud", "tug", "tul", "tun", "tus", "tux",
        "tyc", "tyd", "tyl", "tyn", "typ", "tyr", "tyv", "wac", "wal",
        "wan", "wat", "web", "wed", "weg", "wel", "wen", "wep", "wer",
        "wes", "wet", "wex", "wic", "wid", "win", "wis", "wit", "wol",
        "wor", "wyc", "wyd", "wyl", "wyn", "wyt", "wyx", "zod");
}

void test_affix_pattern() {
    begin_battery("Test affix pattern");
    TestExactAll("dozzod", "bitbet", "betbit");
}

void test_affix_pattern_initial_vowel() {
    begin_battery("Test affix pattern with initial vowel");
    TestExactAll("anzod");
    TestInexactAll("enzod");
}


void begin_battery(const char *name) {
    end_battery();
    battery_name = name;
}

void end_battery() {
    if (this_battery.total == 0) {
        battery_name = 0;
        return;
    }
    batteries.total++;
    if (this_battery.failed > 0)
        batteries.failed++;
    else
        batteries.passed++;
    if (battery_name == 0)
        battery_name = "<anonymous battery>";
    report_battery(battery_name, &this_battery);
    this_battery = (BatteryStats) {};
    battery_name = 0;
}

void report_battery(const char *msg, BatteryStats *stats) {
    printf("%s: %s (passed %d of %d)\n",
           stats->failed ? "Failed" : "Passed",
           msg, stats->passed, stats->total);
}

int tests_done() {
    end_battery();
    report_battery("All test batteries", &batteries);
    return batteries.failed != 0;
}

void test(const char *text, int result, const char *file, int line) {
    total.total++;
    this_battery.total++;
    if (!result) {
        printf("%s:%d: Failed: %s\n", file, line, text);
        total.failed++;
        this_battery.failed++;
    } else {
        total.passed++;
        this_battery.passed++;
    }
}
