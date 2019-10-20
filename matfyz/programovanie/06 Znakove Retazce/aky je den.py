import datetime

rok = int (input ("rok"))
den = int (input ("den"))
mesiac = int (input ("mesiac"))

datum = datetime.date(rok, mesiac, den).strftime("%A")

if datum == "Monday" :
    print ("pon")
if datum == "Tuesday" :
    print ("uto")

print (datum)