class Solution {
public:
	void replaceSpace(char *str,int length) {
        for (int i = 0; i < length; i++) {
            if (str[i] == ' ') {
                for (int j = length; j > i; j--) {
                    str[j + 2] = str[j];
                }
                str[i++] = '%';
                str[i++] = '2';
                str[i] = '0';
                length += 2;
            }
        }
	}
};
