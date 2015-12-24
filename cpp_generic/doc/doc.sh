#/bin/bash
for i in $(find .. | grep -e "\(\.cpp\|\.hpp\|\.h\|\.c\|\.hh\|\.cc\)$"); do 
  echo $i; 
  recode utf-8..latin-1 $i
  a2ps $i -o $i.ps; 
  ps2pdf $i.ps $i.pdf;
done;
rm ../*.ps;
mv ../*.pdf .
