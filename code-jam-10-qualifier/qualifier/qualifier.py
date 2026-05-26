import os

from PIL import Image

def valid_input(image_size: tuple[int, int], tile_size: tuple[int, int], ordering: list[int]) -> bool:
    """
    Return True if the given input allows the rearrangement of the image, False otherwise.

    The tile size must divide each image dimension without remainders, and `ordering` must use each input tile exactly
    once.
    """
    img_x, img_y = image_size
    tile_x, tile_y = tile_size
    if img_x % tile_x != 0 or img_y % tile_y != 0:
        return False
    count_x = img_x // tile_x
    count_y = img_y // tile_y
    count_tot = count_x * count_y
    return sorted(ordering) == list(range(count_tot))


def rearrange_tiles(image_path: str, tile_size: tuple[int, int], ordering: list[int], out_path: str) -> None:
    """
    Rearrange the image.

    The image is given in `image_path`. Split it into tiles of size `tile_size`, and rearrange them by `ordering`.
    The new image needs to be saved under `out_path`.

    The tile size must divide each image dimension without remainders, and `ordering` must use each input tile exactly
    once. If these conditions do not hold, raise a ValueError with the message:
    "The tile size or ordering are not valid for the given image".
    """
    if os.path.exists(out_path):
        if os.path.isfile(out_path):
            os.remove(out_path)
        else:
            raise FileNotFoundError(f"supplied out_path ({out_path}) is a directory", out_path)
    im = Image.open(image_path)
    if not valid_input(im.size, tile_size, ordering):
        raise ValueError("The tile size or ordering are not valid for the given image")
    img_x, img_y = im.size
    tile_x, tile_y = tile_size
    count_x = img_x // tile_x
    count_y = img_y // tile_y
    tiles_orig_order = []
    for j in range(count_y):
        for i in range(count_x):
            curr_tile = im.crop((i*tile_x, j*tile_y, (i+1)*tile_x, (j+1)*tile_y))
            tiles_orig_order.append(curr_tile)
    del curr_tile
    assert len(tiles_orig_order) == len(ordering)
    tiles_sort_order = [tiles_orig_order[ordering[i]] for i in range(len(ordering))]
    pairs_of_coords = [(i, j) for j in range(count_y) for i in range(count_x) ]
    im_out = Image.new(im.mode, im.size)
    for (tile_idx_coords, tile) in zip(pairs_of_coords, tiles_sort_order):
        i, j = tile_idx_coords
        im_out.paste(tile, (i*tile_x, j*tile_y, (i+1)*tile_x, (j+1)*tile_y))
    im_out.save(out_path)
