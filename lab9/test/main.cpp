#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "../Image/Image.h"

TEST(Image, CreateImage)
{
    Image image ({16, 16}, '*');

    for (int y = 0; y < image.GetSize().height; ++y)
    {
        for (int x = 0; x < image.GetSize().width; ++x)
        {
            EXPECT_EQ(image.GetPixel({x, y}), '*');
        }
    }
}

TEST(Image, GetSize)
{
    Image image ({8, 20});

    EXPECT_EQ(image.GetSize().width, 8);
    EXPECT_EQ(image.GetSize().height, 20);
}

TEST(Image, SetAndGetPixel)
{
    Image image({16, 16}, '&');
    EXPECT_EQ(Tile::GetInstanceCount(), 1);

    image.SetPixel({0, 0}, '#');
    EXPECT_EQ(image.GetPixel({0, 0}), '#');
    EXPECT_EQ(Tile::GetInstanceCount(), 2);

    image.SetPixel({10, 10}, '@');
    EXPECT_EQ(image.GetPixel({10, 10}), '@');
    EXPECT_EQ(Tile::GetInstanceCount(), 3);

    image.SetPixel({15, 15}, 'X');
    EXPECT_EQ(image.GetPixel({15, 15}), 'X');
    EXPECT_EQ(Tile::GetInstanceCount(), 3);
}

TEST(Image, GetPixelOutOfBounds)
{
    Image image({16, 16}, '.');

    EXPECT_EQ(image.GetPixel({-1, -1}), 0);
    EXPECT_EQ(image.GetPixel({16, 16}), 0);
}

TEST(Image, SetPixelOutOfBounds)
{
    Image image({16, 16}, '.');

    image.SetPixel({-1, -1}, '#');
    EXPECT_EQ(image.GetPixel({-1, -1}), 0);

    image.SetPixel({16, 16}, '#');
    EXPECT_EQ(image.GetPixel({16, 16}), 0);
}

TEST(Tile, DefaultConstructor)
{
    Tile tile;
    for (int y = 0; y < Tile::SIZE; ++y)
    {
        for (int x = 0; x < Tile::SIZE; ++x)
        {
            EXPECT_EQ(tile.GetPixel({x, y}), 0);
        }
    }

    EXPECT_EQ(Tile::SIZE, 8);

    EXPECT_EQ(Tile::GetInstanceCount(), 1);
}

TEST(Tile, ConstrucorWithParameter)
{
    Tile tile(0xAA);
    EXPECT_EQ(Tile::GetInstanceCount(), 1);

    for (int y = 0; y < Tile::SIZE; ++y)
    {
        for (int x = 0; x < Tile::SIZE; ++x)
        {
            EXPECT_EQ(tile.GetPixel({x, y}), 0xAA);
        }
    }
}

TEST(Tile, CopyConstructor)
{
    Tile tile1('&');
    EXPECT_EQ(Tile::GetInstanceCount(), 1);

    Tile tile2(tile1);
    EXPECT_EQ(Tile::GetInstanceCount(), 2);

    for (int y = 0; y < Tile::SIZE; ++y)
    {
        for (int x = 0; x < Tile::SIZE; ++x)
        {
            EXPECT_EQ(tile2.GetPixel({x, y}), '&');
        }
    }
}

TEST(Tile, SetPixel)
{
    Tile tile(0xAA);

    tile.SetPixel({0, 0}, '#');
    EXPECT_EQ(tile.GetPixel({0, 0}), '#');

    tile.SetPixel({7, 7}, '@');
    EXPECT_EQ(tile.GetPixel({7, 7}), '@');

    tile.SetPixel({8, 8}, 'X');
    EXPECT_EQ(tile.GetPixel({8, 8}), 0);
}

TEST(Tile, GetPixel)
{
    Tile tile('*');

    EXPECT_EQ(tile.GetPixel({4, 4}), '*');
    EXPECT_EQ(tile.GetPixel({2, 1}), '*');
}

TEST(Tile, GetPixelOutOfBound)
{
    Tile tile('*');

    EXPECT_EQ(tile.GetPixel({-1, -1}), 0);
    EXPECT_EQ(tile.GetPixel({8, 8}), 0);
}

TEST(Tile, Destructor)
{
    {
        Tile tile;
        EXPECT_EQ(Tile::GetInstanceCount(), 1);
    }
    EXPECT_EQ(Tile::GetInstanceCount(), 0);
}

TEST(Tile, InstanceCount)
{
    {
        Image img1({8, 8}, '*');
        EXPECT_EQ(Tile::GetInstanceCount(), 1);

        Image img2({8, 8}, '#');
        EXPECT_EQ(Tile::GetInstanceCount(), 2);

        img1.SetPixel({0, 0}, '@');
        EXPECT_EQ(Tile::GetInstanceCount(), 3);
        EXPECT_TRUE((img1.GetPixel({0, 0}) == '@'));
        EXPECT_TRUE(!(img2.GetPixel({0, 0}) == '@'));

        img2.SetPixel({0, 0}, '&');
        EXPECT_EQ(Tile::GetInstanceCount(), 4);
        EXPECT_TRUE((img2.GetPixel({0, 0}) == '&'));
        EXPECT_TRUE(!(img1.GetPixel({0, 0}) == '&'));
    }

    EXPECT_EQ(Tile::GetInstanceCount(), 0);
}

GTEST_API_ int main(int argc, char **argv) {
    ::testing::InitGoogleMock(&argc, argv);
    return RUN_ALL_TESTS();
}