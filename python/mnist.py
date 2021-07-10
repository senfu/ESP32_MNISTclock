import numpy as np
import os
import cv2
import struct
import random
from tqdm import tqdm
import matplotlib.pyplot as plt

def decode_idx3_ubyte(idx3_ubyte_file):
    with open(idx3_ubyte_file, 'rb') as f:
        print('解析文件：', idx3_ubyte_file)
        fb_data = f.read()

    offset = 0
    fmt_header = '>iiii'    # 以大端法读取4个 unsinged int32
    magic_number, num_images, num_rows, num_cols = struct.unpack_from(fmt_header, fb_data, offset)
    print('魔数：{}，图片数：{}'.format(magic_number, num_images))
    offset += struct.calcsize(fmt_header)
    fmt_image = '>' + str(num_rows * num_cols) + 'B'

    images = np.empty((num_images, num_rows, num_cols))
    for i in range(num_images):
        im = struct.unpack_from(fmt_image, fb_data, offset)
        images[i] = np.array(im).reshape((num_rows, num_cols))
        offset += struct.calcsize(fmt_image)
    return images

def decode_idx1_ubyte(idx1_ubyte_file):
    with open(idx1_ubyte_file, 'rb') as f:
        print('解析文件：', idx1_ubyte_file)
        fb_data = f.read()

    offset = 0
    fmt_header = '>ii'  # 以大端法读取两个 unsinged int32
    magic_number, label_num = struct.unpack_from(fmt_header, fb_data, offset)
    print('魔数：{}，标签数：{}'.format(magic_number, label_num))
    offset += struct.calcsize(fmt_header)
    labels = []

    fmt_label = '>B'    # 每次读取一个 byte
    for i in range(label_num):
        labels.append(struct.unpack_from(fmt_label, fb_data, offset)[0])
        offset += struct.calcsize(fmt_label)
    return labels


def export_img(exp_dir, img_ubyte, lable_ubyte):
    images = decode_idx3_ubyte(img_ubyte)
    labels = decode_idx1_ubyte(lable_ubyte)

    nums = len(labels)
    digits = {}
    for x in range(0,10):
        digits[str(x)] = []
    for i in range(nums):
        label = str(labels[i])
        digits[label].append(images[i])
    for digit in range(0,60):
        if digit not in [2]:
            continue
        a = "0" if digit <= 9 else str(digit)[0]
        b = str(digit) if digit <= 9 else str(digit)[1]
        img_a = random.choice(digits[a])
        img_b = random.choice(digits[b])
        imarr = np.concatenate((img_a, img_b), axis=1)
        cv2.imwrite(os.path.join("./number", "{}.png".format(a+b)), imarr)
        

def parser_mnist_data(data_dir):

    # train_dir = os.path.join(data_dir, 'train')
    # train_img_ubyte = os.path.join(data_dir, 'train-images-idx3-ubyte')
    # train_label_ubyte = os.path.join(data_dir, 'train-labels-idx1-ubyte')
    # export_img(train_dir, train_img_ubyte, train_label_ubyte)

    test_dir = os.path.join(data_dir, 'test')
    test_img_ubyte = os.path.join(data_dir, 't10k-images-idx3-ubyte')
    test_label_ubyte = os.path.join(data_dir, 't10k-labels-idx1-ubyte')
    export_img(test_dir, test_img_ubyte, test_label_ubyte)


def Hex(a):
    ret = []
    table = ['0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F']
    while a:
        ret.append(table[a%16])
        a //= 16
    ret.reverse()
    ret = "".join(ret)
    while len(ret) != 2:
        ret = "0"+ret
    return "0X"+ret
    
def transform(data_dir, filename):
    with open(filename, "w") as f:
        f.write("const unsigned char DIGIT_DATA_112x56[] = {\n")
        for digit in range(0,60):
            a = "0" if digit <= 9 else str(digit)[0]
            b = str(digit) if digit <= 9 else str(digit)[1]
            data_name = a+b+'.png'
            img = cv2.imread(os.path.join(data_dir, data_name), cv2.IMREAD_GRAYSCALE)
            img = cv2.threshold(img, 50, 255, cv2.THRESH_BINARY_INV)[1]
            img = cv2.resize(img, dsize=(112, 56))
            img = np.rot90(img)
            img = np.rot90(img)
            img = np.rot90(img)
            img = cv2.flip(img, 1)
            cv2.imwrite(os.path.join('./double/', data_name), img)
            count = 7
            num = 0
            for row in img:
                for pixel in row:
                    num += (1<<count) if pixel >= 128 else 0
                    count -= 1
                    if count < 0:
                        f.write("{},".format(Hex(num)))
                        count = 7
                        num = 0
            f.write(" // digit {}\n".format(str(digit).zfill(2)))
        f.write("};\n")   

if __name__ == '__main__':
    ok_dir = './OK'
    # parser_mnist_data(data_dir)
    transform(ok_dir, 'data.txt')
    for i in range(0, int("0xff",16)+1):
        assert i == int(Hex(i), 16)