from PIL import Image
def collision_grid():
    path = input("Enter :")

    im = Image.open(path)
    pix = im.load()


    T = []

    x,y = im.size
    for k in range(y//64):
        T.append([])
    j=0
    for k in range(0,y,64):
        for i in range(0,x,64):
            if pix[i+32,k+32] == (255,0,0):
                T[k//64].append(1)
            else:
                T[k//64].append(0)
    print(T)

def front_grid():
    img1 = Image.open("grid/auberge_font_grid.png")
    img1 = img1.convert("RGBA")

    img2 = Image.open("Source/Map/auberge.png")
    img2 = img2.convert("RGBA")


    datas1 = img1.getdata()
    datas2 = img2.getdata()

    newData = []
    for k in range(len(datas1)):
        if datas1[k][0] == 0 and datas1[k][1] == 0 and datas1[k][2] ==255:
            newData.append(datas2[k])
        else:
            newData.append((0,0,0,0))



    img1.putdata(newData)
    img1.save("Source/Map/auberge_font.png","PNG")

collision_grid()
