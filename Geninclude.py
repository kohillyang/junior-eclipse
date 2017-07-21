header = '''
<?xml version="1.0" encoding="UTF-8"?>
<cdtprojectproperties>
<section name="org.eclipse.cdt.internal.ui.wizards.settingswizards.IncludePaths">
'''
footer = '''
</section>
</cdtprojectproperties>
'''
includePaths = set()
import os
for x,y,z in os.walk("./"):
    for filename in z:
        if ".h" in filename:
            path = "${ProjDirPath}" + x[1:]
            path = path.replace("/","\\")
            includePaths.add(path)
with open("include_gen.xml","wt") as f:
    f.write(header)
    f.write('''<language name="C Source File">''')            
    f.write("\n")
    for path in includePaths:
        f.write("<includepath>")
        print(path)
        f.write(path)
        f.write("</includepath>")        
        f.write("\n")    

    f.write("</language>\n")            
    f.write('''<language name="C++ Source File">''')            
    f.write("\n")
    for path in includePaths:
        f.write("<includepath>")
        f.write(path)
        f.write("</includepath>")        
        f.write("\n")    

    f.write("</language>\n")            
    
    f.write(footer)
