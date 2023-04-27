#tempFiles oluşturur.
mkdir -p tempFiles
#çalışma yolundaki herşeyi listeler boyutları ve konumlarıyla.
ls -lhR $PWD/*
#çalışma yolunun içeriğini(klasörler hariç) tempFiles'a taşır taşınan dosyalar silinir.
mv ./* ./tempFiles
ls -R $PWD
#tempFiles harici içeriği siler.
rm ./*
ls -R $PWD
#tempFiles klasörünün içeriğini çalışma yoluna kopyalar.
cp ./tempFiles/* ./
ls -R $PWD/*
#tempFiles klasörünü siler.
rm -r ./tempFiles
ls -R $PWD/*
#kaynak kod derlenir compiler gcc.
gcc 152120161061_uyg1B.c -o output.exe
#exe çalıştırılır sonuç txt dosyasına yazdırılır ve karakter sayısı okunur.
###5 kere 2 den büyük sayı giriniz.
./output.exe > ./152120161061_uyg1B_output.txt
wc -m < ./152120161061_uyg1B_output.txt
./output.exe >> ./152120161061_uyg1B_output.txt
wc -m < ./152120161061_uyg1B_output.txt
./output.exe >> ./152120161061_uyg1B_output.txt
wc -m < ./152120161061_uyg1B_output.txt
./output.exe >> ./152120161061_uyg1B_output.txt
wc -m < ./152120161061_uyg1B_output.txt
./output.exe >> ./152120161061_uyg1B_output.txt
wc -m < ./152120161061_uyg1B_output.txt
#çıktı dosyasının içeriği ekrana yazdırılır.
while read -r line;
do
echo "$line";
done < "./152120161061_uyg1B_output.txt"