@echo off
echo Organizing DSA files into topic-based folders...

mkdir "01_Basics" 2>nul
mkdir "02_Math_and_Numbers" 2>nul
mkdir "03_Arrays" 2>nul
mkdir "04_Strings" 2>nul

move "uppercaseandlowercase.cpp" "01_Basics\" >nul 2>&1
move "calculator.cpp" "01_Basics\" >nul 2>&1

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

move "largestSubarrayRearragnement.cpp" "03_Arrays\" >nul 2>&1
move "RemoveElement.cpp" "03_Arrays\" >nul 2>&1
move "removeElement.md" "03_Arrays\" >nul 2>&1
move "RemoveDuplicatefromSortedArray.cpp" "03_Arrays\" >nul 2>&1
move "removeDuplicatesfromsortedarry.md" "03_Arrays\" >nul 2>&1

move "RemoveFirstOccurencefromtheString.cpp" "04_Strings\" >nul 2>&1

echo Organization complete!
pause