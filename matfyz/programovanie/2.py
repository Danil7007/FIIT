
from PIL import Image, ImageDraw, ImageFont
 
c = 0
inc = 10
def create_image_with_text(size, text):
    global c, inc
    img = Image.new('RGB', (350, 50), (255-(c-9),255-(c-9),255-(c-9)))
    draw = ImageDraw.Draw(img)
    draw.text((size[0], size[1]), text, font = fnt, fill=(c,c,c))
    c += inc
        
    return img
 
# Create the frames
frames = []
 
def roll(text):
    global c
    for i in range(len(text)+1):
        new_frame = create_image_with_text((0,0), text[:i])
        frames.append(new_frame)
    c = 0
 
fnt = ImageFont.truetype("arial", 36)
all_text = """
mal by som ist domov
lebo ma tu jebne 
""".splitlines()
[roll(text) for text in all_text]
 
 
# Save into a GIF file that loops forever
frames[0].save('banner_c.gif', format='GIF',
               append_images=frames[1:], save_all=True, duration=80, loop=0)
print("Done")
