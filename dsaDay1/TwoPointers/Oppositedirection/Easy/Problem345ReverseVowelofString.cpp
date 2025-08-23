class Solution
{
public:
    bool isVowel(char c)
    {
        c = tolower(c);
        return (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u');
    }

    string reverseVowels(string s)
    {
        int left = 0, right = s.length() - 1;

        while (left < right)
        {
            if (isVowel(s[left]) && isVowel(s[right]))
            {
                swap(s[left], s[right]);
                left++;
                right--;
            }
            else if (!isVowel(s[left]))
            {
                left++;
            }
            else if (!isVowel(s[right]))
            {
                right--;
            }
        }
        return s;
    }
};