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


#define Test(input, expected) test(input, expected, __FILE__, __LINE__)
void test(const char *input, int expected, const char *file, int line);

void begin_battery(const char *name);
void end_battery();
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


void test_one_letter() {
    begin_battery("test_one_letter");
    Test("a", 1);  Test("b", 1);  Test("c", 1);
    Test("d", 1);  Test("e", 1);  Test("f", 1);
    Test("g", 1);  Test("h", 1);  Test("i", 1);
    Test("j", 0);  Test("k", 0);  Test("l", 1);
    Test("m", 1);  Test("n", 1);  Test("o", 1);
    Test("p", 1);  Test("q", 0);  Test("r", 1);
    Test("s", 1);  Test("t", 1);  Test("u", 1);
    Test("v", 1);  Test("w", 1);  Test("x", 1);
    Test("y", 1);  Test("z", 1);
}

void test_two_letters() {
    begin_battery("test_two_letters");
    Test("aa", 0);  Test("ab", 1);  Test("ac", 1);  Test("ad", 1);
    Test("ae", 0);  Test("af", 0);  Test("ag", 1);  Test("ah", 0);
    // TODO: write more tests here
}

void test_literal_syllables() {
    begin_battery("test_literal_syllables");
    Test("bac", 1);  Test("bal", 1);  Test("ban", 1);  Test("bar", 1);
    Test("bat", 1);  Test("bec", 1);  Test("bel", 1);  Test("ben", 1);
    Test("bep", 1);  Test("ber", 1);  Test("bes", 1);  Test("bet", 1);
    Test("bex", 1);  Test("bic", 1);  Test("bid", 1);  Test("bil", 1);
    Test("bin", 1);  Test("bis", 1);  Test("bit", 1);  Test("bol", 1);
    Test("bon", 1);  Test("bor", 1);  Test("bos", 1);  Test("bot", 1);
    Test("bud", 1);  Test("bur", 1);  Test("bus", 1);  Test("byl", 1);
    Test("byn", 1);  Test("byr", 1);  Test("byt", 1);  Test("dab", 1);
    Test("dac", 1);  Test("dal", 1);  Test("dan", 1);  Test("dap", 1);
    Test("dar", 1);  Test("das", 1);  Test("dat", 1);  Test("dav", 1);
    Test("deb", 1);  Test("dec", 1);  Test("def", 1);  Test("deg", 1);
    Test("del", 1);  Test("dem", 1);  Test("den", 1);  Test("dep", 1);
    Test("der", 1);  Test("des", 1);  Test("det", 1);  Test("dev", 1);
    Test("dex", 1);  Test("dib", 1);  Test("dif", 1);  Test("dig", 1);
    Test("dil", 1);  Test("din", 1);  Test("dir", 1);  Test("dis", 1);
    Test("div", 1);  Test("doc", 1);  Test("dol", 1);  Test("don", 1);
    Test("dop", 1);  Test("dor", 1);  Test("dos", 1);  Test("dot", 1);
    Test("dov", 1);  Test("doz", 1);  Test("duc", 1);  Test("dul", 1);
    Test("dun", 1);  Test("dur", 1);  Test("dus", 1);  Test("dut", 1);
    Test("dux", 1);  Test("dyl", 1);  Test("dyn", 1);  Test("dyr", 1);
    Test("dys", 1);  Test("dyt", 1);  Test("fab", 1);  Test("fad", 1);
    Test("fal", 1);  Test("fam", 1);  Test("fan", 1);  Test("fas", 1);
    Test("feb", 1);  Test("fed", 1);  Test("fel", 1);  Test("fen", 1);
    Test("fep", 1);  Test("fer", 1);  Test("fes", 1);  Test("fet", 1);
    Test("fex", 1);  Test("fid", 1);  Test("fig", 1);  Test("fil", 1);
    Test("fin", 1);  Test("fip", 1);  Test("fir", 1);  Test("fit", 1);
    Test("fod", 1);  Test("fog", 1);  Test("fol", 1);  Test("fon", 1);
    Test("fop", 1);  Test("for", 1);  Test("fos", 1);  Test("fot", 1);
    Test("ful", 1);  Test("fun", 1);  Test("fur", 1);  Test("fus", 1);
    Test("fyl", 1);  Test("fyn", 1);  Test("fyr", 1);  Test("hab", 1);
    Test("hac", 1);  Test("had", 1);  Test("hal", 1);  Test("han", 1);
    Test("hap", 1);  Test("har", 1);  Test("has", 1);  Test("hat", 1);
    Test("hav", 1);  Test("heb", 1);  Test("hec", 1);  Test("hep", 1);
    Test("hes", 1);  Test("het", 1);  Test("hex", 1);  Test("hid", 1);
    Test("hil", 1);  Test("hin", 1);  Test("hob", 1);  Test("hoc", 1);
    Test("hod", 1);  Test("hol", 1);  Test("hop", 1);  Test("hos", 1);
    Test("hul", 1);  Test("hus", 1);  Test("hut", 1);  Test("lab", 1);
    Test("lac", 1);  Test("lad", 1);  Test("lag", 1);  Test("lan", 1);
    Test("lap", 1);  Test("lar", 1);  Test("las", 1);  Test("lat", 1);
    Test("lav", 1);  Test("leb", 1);  Test("lec", 1);  Test("led", 1);
    Test("leg", 1);  Test("len", 1);  Test("lep", 1);  Test("ler", 1);
    Test("let", 1);  Test("lev", 1);  Test("lex", 1);  Test("lib", 1);
    Test("lid", 1);  Test("lig", 1);  Test("lin", 1);  Test("lis", 1);
    Test("lit", 1);  Test("liv", 1);  Test("loc", 1);  Test("lod", 1);
    Test("lom", 1);  Test("lon", 1);  Test("lop", 1);  Test("lor", 1);
    Test("los", 1);  Test("luc", 1);  Test("lud", 1);  Test("lug", 1);
    Test("lun", 1);  Test("lup", 1);  Test("lur", 1);  Test("lus", 1);
    Test("lut", 1);  Test("lux", 1);  Test("lyd", 1);  Test("lyn", 1);
    Test("lyr", 1);  Test("lys", 1);  Test("lyt", 1);  Test("lyx", 1);
    Test("mac", 1);  Test("mag", 1);  Test("mal", 1);  Test("map", 1);
    Test("mar", 1);  Test("mas", 1);  Test("mat", 1);  Test("meb", 1);
    Test("mec", 1);  Test("med", 1);  Test("meg", 1);  Test("mel", 1);
    Test("mep", 1);  Test("mer", 1);  Test("mes", 1);  Test("met", 1);
    Test("mev", 1);  Test("mex", 1);  Test("mic", 1);  Test("mid", 1);
    Test("mig", 1);  Test("mil", 1);  Test("min", 1);  Test("mip", 1);
    Test("mir", 1);  Test("mis", 1);  Test("mit", 1);  Test("moc", 1);
    Test("mod", 1);  Test("mog", 1);  Test("mol", 1);  Test("mon", 1);
    Test("mop", 1);  Test("mor", 1);  Test("mos", 1);  Test("mot", 1);
    Test("mud", 1);  Test("mug", 1);  Test("mul", 1);  Test("mun", 1);
    Test("mur", 1);  Test("mus", 1);  Test("mut", 1);  Test("myl", 1);
    Test("myn", 1);  Test("myr", 1);  Test("nac", 1);  Test("nal", 1);
    Test("nam", 1);  Test("nap", 1);  Test("nar", 1);  Test("nat", 1);
    Test("nav", 1);  Test("neb", 1);  Test("nec", 1);  Test("ned", 1);
    Test("nel", 1);  Test("nem", 1);  Test("nep", 1);  Test("ner", 1);
    Test("nes", 1);  Test("net", 1);  Test("nev", 1);  Test("nex", 1);
    Test("nib", 1);  Test("nid", 1);  Test("nil", 1);  Test("nim", 1);
    Test("nis", 1);  Test("noc", 1);  Test("nod", 1);  Test("nol", 1);
    Test("nom", 1);  Test("nop", 1);  Test("nor", 1);  Test("nos", 1);
    Test("nov", 1);  Test("nub", 1);  Test("nul", 1);  Test("num", 1);
    Test("nup", 1);  Test("nus", 1);  Test("nut", 1);  Test("nux", 1);
    Test("nyd", 1);  Test("nyl", 1);  Test("nym", 1);  Test("nyr", 1);
    Test("nys", 1);  Test("nyt", 1);  Test("nyx", 1);  Test("pac", 1);
    Test("pad", 1);  Test("pag", 1);  Test("pal", 1);  Test("pan", 1);
    Test("par", 1);  Test("pas", 1);  Test("pat", 1);  Test("pec", 1);
    Test("ped", 1);  Test("peg", 1);  Test("pel", 1);  Test("pem", 1);
    Test("pen", 1);  Test("per", 1);  Test("pes", 1);  Test("pet", 1);
    Test("pex", 1);  Test("pic", 1);  Test("pid", 1);  Test("pil", 1);
    Test("pin", 1);  Test("pit", 1);  Test("poc", 1);  Test("pod", 1);
    Test("pol", 1);  Test("pon", 1);  Test("pos", 1);  Test("pub", 1);
    Test("pun", 1);  Test("pur", 1);  Test("put", 1);  Test("pyl", 1);
    Test("pyx", 1);  Test("rab", 1);  Test("rac", 1);  Test("rad", 1);
    Test("rag", 1);  Test("ral", 1);  Test("ram", 1);  Test("ran", 1);
    Test("rap", 1);  Test("rav", 1);  Test("reb", 1);  Test("rec", 1);
    Test("red", 1);  Test("ref", 1);  Test("reg", 1);  Test("rel", 1);
    Test("rem", 1);  Test("ren", 1);  Test("rep", 1);  Test("res", 1);
    Test("ret", 1);  Test("rev", 1);  Test("rex", 1);  Test("rib", 1);
    Test("ric", 1);  Test("rid", 1);  Test("rig", 1);  Test("ril", 1);
    Test("rin", 1);  Test("rip", 1);  Test("ris", 1);  Test("rit", 1);
    Test("riv", 1);  Test("roc", 1);  Test("rol", 1);  Test("ron", 1);
    Test("rop", 1);  Test("ros", 1);  Test("rov", 1);  Test("ruc", 1);
    Test("rud", 1);  Test("rul", 1);  Test("rum", 1);  Test("run", 1);
    Test("rup", 1);  Test("rus", 1);  Test("rut", 1);  Test("rux", 1);
    Test("ryc", 1);  Test("ryd", 1);  Test("ryg", 1);  Test("ryl", 1);
    Test("rym", 1);  Test("ryn", 1);  Test("ryp", 1);  Test("rys", 1);
    Test("ryt", 1);  Test("ryx", 1);  Test("sab", 1);  Test("sal", 1);
    Test("sam", 1);  Test("san", 1);  Test("sap", 1);  Test("sar", 1);
    Test("sat", 1);  Test("sav", 1);  Test("seb", 1);  Test("sec", 1);
    Test("sed", 1);  Test("sef", 1);  Test("seg", 1);  Test("sel", 1);
    Test("sem", 1);  Test("sen", 1);  Test("sep", 1);  Test("ser", 1);
    Test("set", 1);  Test("sev", 1);  Test("sib", 1);  Test("sic", 1);
    Test("sid", 1);  Test("sig", 1);  Test("sil", 1);  Test("sim", 1);
    Test("sip", 1);  Test("sit", 1);  Test("siv", 1);  Test("soc", 1);
    Test("sog", 1);  Test("sol", 1);  Test("som", 1);  Test("son", 1);
    Test("sop", 1);  Test("sor", 1);  Test("sov", 1);  Test("sub", 1);
    Test("sud", 1);  Test("sug", 1);  Test("sul", 1);  Test("sum", 1);
    Test("sun", 1);  Test("sup", 1);  Test("sur", 1);  Test("sut", 1);
    Test("syd", 1);  Test("syl", 1);  Test("sym", 1);  Test("syn", 1);
    Test("syp", 1);  Test("syr", 1);  Test("syt", 1);  Test("syx", 1);
    Test("tab", 1);  Test("tac", 1);  Test("tad", 1);  Test("tag", 1);
    Test("tal", 1);  Test("tam", 1);  Test("tan", 1);  Test("tap", 1);
    Test("tar", 1);  Test("tas", 1);  Test("teb", 1);  Test("tec", 1);
    Test("ted", 1);  Test("teg", 1);  Test("tel", 1);  Test("tem", 1);
    Test("ten", 1);  Test("tep", 1);  Test("ter", 1);  Test("tes", 1);
    Test("tev", 1);  Test("tex", 1);  Test("tic", 1);  Test("tid", 1);
    Test("til", 1);  Test("tim", 1);  Test("tin", 1);  Test("tip", 1);
    Test("tir", 1);  Test("tob", 1);  Test("toc", 1);  Test("tod", 1);
    Test("tog", 1);  Test("tol", 1);  Test("tom", 1);  Test("ton", 1);
    Test("top", 1);  Test("tor", 1);  Test("tuc", 1);  Test("tud", 1);
    Test("tug", 1);  Test("tul", 1);  Test("tun", 1);  Test("tus", 1);
    Test("tux", 1);  Test("tyc", 1);  Test("tyd", 1);  Test("tyl", 1);
    Test("tyn", 1);  Test("typ", 1);  Test("tyr", 1);  Test("tyv", 1);
    Test("wac", 1);  Test("wal", 1);  Test("wan", 1);  Test("wat", 1);
    Test("web", 1);  Test("wed", 1);  Test("weg", 1);  Test("wel", 1);
    Test("wen", 1);  Test("wep", 1);  Test("wer", 1);  Test("wes", 1);
    Test("wet", 1);  Test("wex", 1);  Test("wic", 1);  Test("wid", 1);
    Test("win", 1);  Test("wis", 1);  Test("wit", 1);  Test("wol", 1);
    Test("wor", 1);  Test("wyc", 1);  Test("wyd", 1);  Test("wyl", 1);
    Test("wyn", 1);  Test("wyt", 1);  Test("wyx", 1);  Test("zod", 1);
}

void test_affix_pattern() {
}

void test_affix_pattern_initial_vowel() {
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
    if (this_battery.failed > 0)
        printf("%s: failed %d/%d tests\n", battery_name,
               this_battery.failed, this_battery.total);
    else
        printf("%s: passed %d/%d tests\n", battery_name,
               this_battery.passed, this_battery.total);
    this_battery = (BatteryStats) {};
    battery_name = 0;
}

int tests_done() {
    end_battery();
    if (batteries.failed > 0) {
        printf("Failed %d/%d batteries.\n",
               batteries.failed, batteries.total);
        return 1;
    }

    printf("Passed %d/%d batteries (%d/%d tests).\n", batteries.passed,
           batteries.total, total.passed, total.total);
    return 0;
}


int valid_word(const char *line);

void test(const char *input, int expected, const char *file, int line) {
    total.total++;
    this_battery.total++;
    int actual = valid_word(input);
    if (expected != actual) {
        printf("%s:%d: %s: expected = %d; actual = %d\n", file, line,
               input, expected, actual);
        total.failed++;
        this_battery.failed++;
    } else {
        total.passed++;
        this_battery.passed++;
    }
}
