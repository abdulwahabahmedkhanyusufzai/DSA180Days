@echo off
echo Organizing DSA files into topic-based folders...

mkdir "01_Basics" 2>nul
mkdir "02_Math_and_Numbers" 2>nul
mkdir "03_Arrays" 2>nul
mkdir "04_Strings" 2>nul
mkdir "05_Two_Pointers" 2>nul
mkdir "06_Recursion" 2>nul

:: Basics
move "uppercaseandlowercase.cpp" "01_Basics\" >nul 2>&1
move "calculator.cpp" "01_Basics\" >nul 2>&1
move "learnC++\inputoutput.cpp" "01_Basics\" >nul 2>&1

:: Math
move "gcdofTwoNumber.cpp" "02_Math_and_Numbers\" >nul 2>&1
move "primeNumber.cpp" "02_Math_and_Numbers\" >nul 2>&1
move "armstrongNumber.cpp" "02_Math_and_Numbers\" >nul 2>&1
move "CountDigits.cpp" "02_Math_and_Numbers\" >nul 2>&1
move "reverseaNum.cpp" "02_Math_and_Numbers\" >nul 2>&1
move "palindromeNumber.cpp" "02_Math_and_Numbers\" >nul 2>&1
move "commonDivisors.cpp" "02_Math_and_Numbers\" >nul 2>&1
move "quotientdivison.md" "02_Math_and_Numbers\" >nul 2>&1
:: Renaming code.cpp to something more descriptive
move "code.cpp" "02_Math_and_Numbers\divideTwoIntegers.cpp" >nul 2>&1

:: Arrays
move "largestSubarrayRearragnement.cpp" "03_Arrays\" >nul 2>&1
move "RemoveElement.cpp" "03_Arrays\" >nul 2>&1
move "removeElement.md" "03_Arrays\" >nul 2>&1
move "RemoveDuplicatefromSortedArray.cpp" "03_Arrays\" >nul 2>&1
move "removeDuplicatesfromsortedarry.md" "03_Arrays\" >nul 2>&1
move "dsaDay1\ArrayIntro\Array.md" "03_Arrays\" >nul 2>&1
move "learnC++\PrefixSum.txt" "03_Arrays\" >nul 2>&1

:: Strings
move "RemoveFirstOccurencefromtheString.cpp" "04_Strings\" >nul 2>&1

:: Two Pointers
move "dsaDay1\TwoPointers\TwoPointerQsEasy.md" "05_Two_Pointers\" >nul 2>&1
move "dsaDay1\TwoPointers\slowfastpointer\Easy\Problem26RemoveDuplicatesfromSortedArrays.md" "05_Two_Pointers\" >nul 2>&1
move "dsaDay1\TwoPointers\Oppositedirection\Easy\easy.cpp" "05_Two_Pointers\removeDuplicates_OppositeDirection.cpp" >nul 2>&1

:: Recursion
move "print1toNusingRecursion.cpp" "06_Recursion\" >nul 2>&1
move "reverseArrayusingRecurson.cpp" "06_Recursion\" >nul 2>&1

:: Cleanup empty old directories
rmdir /S /Q "dsaDay1" 2>nul
rmdir /S /Q "learnC++" 2>nul

echo Organization complete! Old nested folders have been cleaned up.
pause