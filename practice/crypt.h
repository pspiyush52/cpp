#ifndef __CRYPT_H
#define __CRYPT_H
#define SIZE 30

#include <cctype>

class perm_ed{
    protected:
        using ull = unsigned long long;
        ull __size{SIZE};
        const char* __keys[SIZE] = {
            "dwsevfrcqxaztjhuygmbnlokpi", "qxawzsegcfdtrbvpkuijolmnhy",
            "kmpoilnjthfvgybucqdaswezxr", "jdzuofcqbvirmxgknhelwpasyt",
            "rjaghcxfpmozqnbsdyuvwkielt", "nfwspczblidaxguqorhkyjtvme",
            "uohyfmgswqvatcelzkrpixdbjn", "eaujxkdybpchozqvrtnmsgwfli",
            "reczbsdwnvokxyhfptaumqglji", "ljuvnxtqofzrkwpdegimabyhsc",
            "ygfaidqtlhkuvxjrsmnzcepwbo", "rckhpbwqangtlvdzexsufoiyjm",
            "qhctjaeifdlnskobrwuzmvygxp", "qirlpthabvowdkuzysegjxnmfc",
            "veshlmkioqjbxtpgdacwuyrznf", "cspzbfhkamiyqxvrjungtleodw",
            "nzeovujdkpqacmxwgyrlhfsbti", "wztxkeypovgdqhmsujbrnfilca",
            "pbxrfuthgaqjcsdoyilvmwenkz", "deiltavkwrmxojpysznfbcguqh",
            "coiepklhdzmywbjxgqvursnatf", "wgrcqvxildsfezubnayotpjhkm",
            "bjlpekrnfiqhguzvytdaocmxws", "dxpcmegykonisqwfrtlvaubjhz",
            "juwakcorizxylmgsfdhvqntepb", "ijykrvfnhawzpqgocmdxlteubs",
            "lwnayxgkjotdpsfmqzebhiucvr", "idkupoqwvmncyhatxjzefgrbsl",
            "xaqnzhkbtmerwdysclfjopugvi", "jepktyvacouhwsgqdmlrnbxzif"
        };
        const char* __decrypt[SIZE] = {
            "kthadfroznxvsuwyigcmpebjql", "cnikgjhystqvwxupamflrodbze",
            "toqswkmjehafbgdcrzuiplvynx", "wigbsforkaptmqevhlxzdjunyc",
            "cofqxhdewbvyjnkimapzstugrl", "lhfkzbnsjvtiyaqeprdwoxcmug",
            "lxnwoegcuyrpfzbtjshmakivdq", "bikgaxvlzdfytsmjoqurcpwehn",
            "secgbpwozylxuikqvafrtjhmnd", "uvzpqjrxsbmateiohlygcdnfwk",
            "dyufvcbjeokirszwgpqhlmxnat", "ifboqukdwycmzjvehasltngrxp",
            "fpcjgixbhenkulozaqmdsvrywt", "hizmsytgbundxwkeacrfojlvqp",
            "rlsqbzpdhkgefyiojwcnuatmvx", "ieaywftgkqhvjsxcmpburoznld",
            "lxmhcvquzgitnadjkswyfeporb", "zsylfvknwrexouihmtpcqjadgb",
            "jbmoweihrlysuxpakdngftvcqz", "fuvabtwzcnhdksmoyjqexgilpr",
            "xnaidzqhcofgkwberuvytsmplj", "rpdjmlbxhwyizqtveckuofagsn",
            "tavseimljbfcwhudkgzrnpyxqo", "uwdafpgylxisekjcnqmrvtobhz",
            "dzfrxqosiaemnvgyuhpwbtcklj", "jyqswgoiabdurhpmnezvxfktcl",
            "dtxlsoguvihapcjmqznkwybfer", "oxlbtuvnarczjkfegwypdihqms",
            "bhqnksxfztgrjduvclpiwymaoe", "hviqbzolyadsrujcptnekgmwfx"
        };
};

class perm_encrypt : public perm_ed{
    public:
        void operator()(char* str, ull size){
            const char* key;
            char cur{};
            for (ull i{}; i < size; ++i){
                if (std::isalpha(str[i])){
                    key = this->__keys[i % this->__size];
                    if (std::isupper(str[i]))
                        str[i] = std::toupper(key[str[i] - 'A']);
                    else
                        str[i] = key[str[i] - 'a'];
                }
            }
        }
};

class perm_decrypt : public perm_ed{
    public:
        void operator()(char* str, ull size){
            const char* key;
            for (ull i{}; i < size; ++i){
                if (std::isalpha(str[i])){
                    key = this->__decrypt[i % this->__size];
                    if (std::isupper(str[i]))
                        str[i] = std::toupper(key[str[i] - 'A']);
                    else
                        str[i] = key[str[i] - 'a'];
                }
            }
        }
};

#endif  // __CRYPT_H