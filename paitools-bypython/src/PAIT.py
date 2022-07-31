# -*- coding: utf-8 -*-
# dot4dow
import sys
import wand.image
#from wand.image import Image
import PySimpleGUI as sg
from pdf2image import convert_from_path

"""
    Two popup windows and two function 

    The first function is convert the pdf to image
    The second function is convert the fromat of input image

    Copyright 2022 https://pysimplegui.readthedocs.io/en/latest/
    Copyright 2022 https://docs.wand-py.org/en/0.6.7/
    Copyright 2022 https://github.com/Belval/pdf2image/
"""

def PDF2Image():
    sg.theme("NeutralBlue")
    layout = [
        [
            sg.Text("Source PDF", size=(10, 1)),
            sg.InputText(default_text="Choose a PDF", size=(60, 1)),
            sg.FileBrowse(key = '-GETFILE-'),
            ],
        [
            sg.Text("Output Folder", size=(10, 1)),
            sg.InputText(default_text="Choose a folder", size=(60, 1)),
            sg.FolderBrowse(key = '-GETFOLDER-'),
            ],
        [
            sg.Text("Output Name", size=(10, 1)),
            sg.InputText(default_text="Input a out file name",key = '-GETFILENAME-',size=(60, 1)),
            ],
        [
            sg.Frame(
                layout=[
                    [
                        sg.Text("Resolution/dpi", size=(15,1)),
                        sg.Combo(('76','92','300','600','800','1200'),
                                 default_value='300',
                                 key = '-DPI-',
                                 size=(5, 1),),
                        ],
                    [
                        sg.Text("Output Format", size=(15,1)),
                        sg.Combo(('jpeg','png','ppm','tiff'),
                                 default_value='jpeg',
                                 key = '-FORMAT-',size=(5, 1),),
                        sg.Text("", size=(22, 1)),
                        sg.Submit("Convert", size=(25, 1)),
                        ],
                    [sg.ProgressBar(100, orientation="h", key = '-BAR-', size=(74.3, 20))],
                    ],
                title="Advance options",
                relief=sg.RELIEF_GROOVE,
                )
            ],
        ]

    window = sg.Window("PDF CONVERT TO IMAGE", layout, icon='Bell.ico', finalize = True)

    while True:
        event, values = window.read()
        
        
        #print(event, values)
        if event == "Cancel" or event is None:
            return 0
        
        # get the args value
        else :
            in_pdf = values['-GETFILE-']
            out_path = str(values['-GETFOLDER-']) 
            res = values['-DPI-']
            outformat = values['-FORMAT-']
            outname = values['-GETFILENAME-']
            progress_bar = window['-BAR-']
                             
            images = convert_from_path(in_pdf,
                                       dpi=res,
                                       jpegopt={"quality": 100,
                                                "progressive": True,
                                                "optimize": True},
                                       fmt=outformat,
                                       first_page=None,
                                       last_page=None,
                                       single_file=True,
                                       poppler_path=r'.\poppler-0.68.0\bin',
                                       output_folder=out_path,
                                       output_file=outname)
        for i in range(1000):
                progress_bar.UpdateBar(i + 1)
                
        sg.popup_ok('Conversion successful!',title = None) 
    return sg.Window('PDF CONVERT TO IMAGE', layout, icon='Bell.ico', finalize = True)


def img_format_converter():
    sg.theme("NeutralBlue")
    layout = [
        [
            sg.Text("Source Image", size=(10, 1)),
            sg.InputText(default_text="Choose a Image File", size=(60, 1)),
            sg.FileBrowse(key = '-GETFILE-'),
            ],
        [
            sg.Text("Output Folder", size=(10, 1)),
            sg.InputText(default_text="Choose a folder", size=(60, 1)),
            sg.FolderBrowse(key = '-GETFOLDER-'),
            ],
        [
            sg.Text("Output Name", size=(10, 1)),
            sg.InputText(default_text="Input a out file name",key = '-GETFILENAME-',size=(60, 1)),
            ],
        [
            sg.Frame(
                layout=[
                    [
                        sg.Text('Original Resolution Will Be Preserved.',size=(40,1)),
                        ],
                    [
                        sg.Text("Output Format", size=(15,1)),
                        sg.Combo(('jpeg','png','ppm','tiff','svg','eps','bmp','pdf','ps'),
                                 default_value='jpeg',
                                 key = '-FORMAT-',
                                 size=(5, 1),),
                        sg.Text("", size=(22, 1)),
                        sg.Submit("Convert", size=(25, 1)),
                        ],
                    [sg.ProgressBar(100, orientation="h", key = '-BAR-', size=(74.3, 20))],
                    ],
                title="Advance options",
                relief=sg.RELIEF_GROOVE,
                )
            ],
        ]

    window = sg.Window("IMAGE FORMAT CONVERTER", layout, icon='Bell.ico', finalize = True)

    while True:
        event, values = window.read()
        
        
        #print(event, values)
        if event == "Cancel" or event is None:
            return 0
        
        # get the args value
        else :
            input_image = values['-GETFILE-']
            out_path = str(values['-GETFOLDER-']) 
            outformat = values['-FORMAT-']
            outname = values['-GETFILENAME-']
            progress_bar = window['-BAR-']
            with wand.image.Image(filename=input_image) as original:
                with original.convert(outformat) as converted:
                    if "." in outname:
                        outputfile = str(out_path) + "\\" + str(outname).split(".")[0] + "_converted." + outformat
                    else :
                        outputfile = str(out_path) + "\\" + str(outname) + "_converted." + outformat
                    # operations to a jpeg image...
                    converted.save(filename=outputfile)
        for i in range(1000):
                progress_bar.UpdateBar(i + 1)
                
        sg.popup_ok('Conversion successful!',title = None) 
    return sg.Window('IMAGE FORMAT CONVERTER', layout, location = (800,600), icon='Bell.ico', finalize = True)

def MainWindows():
    sg.theme("GreenMono")
    layout = [
        [
            sg.Text('PDF AND IMAGE TOOLS')
            ],
        [
            sg.Text('PLEASE SELECT THE FUNCTION YOU NEED !')
         ],
        [
            sg.Frame(
                layout = [
                    [
                        sg.Button('PDF CONVERT TO IMAGE'),
                        sg.Button('IMAGE FORMAT CONVERTER'),
                        sg.Button('EXIT')
                        ],
                    ],
    title="Advance options",
    relief=sg.RELIEF_GROOVE)
        ]]
    return sg.Window('PAIT', layout, icon='Bell.ico', finalize = True)



def loopwindow():
    window1, window2 ,window3= MainWindows(), None, None
    while True:
        window, event, values = sg.read_all_windows()
        if event == sg.WIN_CLOSED or event == 'EXIT':
            window.close()
            if window == window3:
                window3 = None
            elif window == window2:
                window2 = None
            elif window == window1:
                break
        elif event == 'PDF CONVERT TO IMAGE' and not window2:
            window2 = PDF2Image()
        elif event == 'IMAGE FORMAT CONVERTER' and not window3:
            window3 = img_format_converter()
    window.close()

if __name__ == "__main__":
    loopwindow()
