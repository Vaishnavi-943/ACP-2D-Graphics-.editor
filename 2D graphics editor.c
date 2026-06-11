#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define WIDTH 80
#define HEIGHT 25
#define MAX_OBJECTS 100

// Shape Types
typedef enum
{
    LINE,
    RECTANGLE,
    CIRCLE,
    TRIANGLE
} ShapeType;

// Shape Structure
typedef struct
{
    ShapeType type;
    int x1, y1, x2, y2;
    int base, height;
    int radius;
} Shape;

char canvas[HEIGHT][WIDTH];
Shape objects[MAX_OBJECTS];
int objectCount = 0;

// Function Prototypes
void clearCanvas();
void plot(int x, int y);
void drawLine(int x1, int y1, int x2, int y2);
void drawRectangle(int x1, int y1, int x2, int y2);
void drawCircle(int xc, int yc, int r);
void drawRightTriangle(int x, int y, int base, int height);
void redraw();
void displayCanvas();
void addObject(Shape s);
void deleteObject(int index);
void modifyObject(int index, Shape s);

// Clear Canvas
void clearCanvas()
{
    for (int i = 0; i < HEIGHT; i++)
    {
        for (int j = 0; j < WIDTH; j++)
        {
            canvas[i][j] = '_';
        }
    }
}

// Plot a Point
void plot(int x, int y)
{
    if (x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT)
        canvas[y][x] = '*';
}

// Bresenham Line Drawing
void drawLine(int x1, int y1, int x2, int y2)
{
    int dx = abs(x2 - x1);
    int dy = abs(y2 - y1);

    int sx = (x1 < x2) ? 1 : -1;
    int sy = (y1 < y2) ? 1 : -1;

    int err = dx - dy;

    while (1)
    {
        plot(x1, y1);

        if (x1 == x2 && y1 == y2)
            break;

        int e2 = 2 * err;

        if (e2 > -dy)
        {
            err -= dy;
            x1 += sx;
        }

        if (e2 < dx)
        {
            err += dx;
            y1 += sy;
        }
    }
}

// Rectangle
void drawRectangle(int x1, int y1, int x2, int y2)
{
    drawLine(x1, y1, x2, y1);
    drawLine(x2, y1, x2, y2);
    drawLine(x2, y2, x1, y2);
    drawLine(x1, y2, x1, y1);
}

// Circle
void drawCircle(int xc, int yc, int r)
{
    int x = 0;
    int y = r;
    int d = 3 - 2 * r;

    while (x <= y)
    {
        plot(xc + x, yc + y);
        plot(xc - x, yc + y);
        plot(xc + x, yc - y);
        plot(xc - x, yc - y);
        plot(xc + y, yc + x);
        plot(xc - y, yc + x);
        plot(xc + y, yc - x);
        plot(xc - y, yc - x);

        if (d < 0)
            d += 4 * x + 6;
        else
        {
            d += 4 * (x - y) + 10;
            y--;
        }
        x++;
    }
}

// Right-Angled Triangle
void drawRightTriangle(int x, int y, int base, int height)
{
    // Left side
    drawLine(x, y, x, y + height);

    // Bottom side
    drawLine(x, y + height, x + base, y + height);

    // Hypotenuse
    drawLine(x, y, x + base, y + height);
}

// Add Object
void addObject(Shape s)
{
    if (objectCount < MAX_OBJECTS)
        objects[objectCount++] = s;
}

// Delete Object
void deleteObject(int index)
{
    if (index < 0 || index >= objectCount)
        return;

    for (int i = index; i < objectCount - 1; i++)
        objects[i] = objects[i + 1];

    objectCount--;
}

// Modify Object
void modifyObject(int index, Shape s)
{
    if (index >= 0 && index < objectCount)
        objects[index] = s;
}

// Redraw All Objects
void redraw()
{
    clearCanvas();

    for (int i = 0; i < objectCount; i++)
    {
        Shape s = objects[i];

        switch (s.type)
        {
        case LINE:
            drawLine(s.x1, s.y1, s.x2, s.y2);
            break;

        case RECTANGLE:
            drawRectangle(s.x1, s.y1, s.x2, s.y2);
            break;

        case CIRCLE:
            drawCircle(s.x1, s.y1, s.radius);
            break;

        case TRIANGLE:
            drawRightTriangle(s.x1, s.y1, s.base, s.height);
            break;
        }
    }
}

// Display Canvas
void displayCanvas()
{
    for (int i = 0; i < HEIGHT; i++)
    {
        for (int j = 0; j < WIDTH; j++)
            printf("%c", canvas[i][j]);
        printf("\n");
    }
}

// Main Function
int main()
{
    int choice, index;
    Shape s;

    clearCanvas();

    while (1)
    {
        printf("\n===== 2D Graphics Editor =====\n");
        printf("1. Add Line\n");
        printf("2. Add Rectangle\n");
        printf("3. Add Circle\n");
        printf("4. Add 90 Degree Triangle\n");
        printf("5. Delete Object\n");
        printf("6. Modify Object\n");
        printf("7. Display Picture\n");
        printf("8. Exit\n");

        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            s.type = LINE;
            printf("Enter x1 y1 x2 y2: ");
            scanf("%d%d%d%d", &s.x1, &s.y1, &s.x2, &s.y2);
            addObject(s);
            redraw();
            break;

        case 2:
            s.type = RECTANGLE;
            printf("Enter x1 y1 x2 y2: ");
            scanf("%d%d%d%d", &s.x1, &s.y1, &s.x2, &s.y2);
            addObject(s);
            redraw();
            break;

        case 3:
            s.type = CIRCLE;
            printf("Enter center x y and radius: ");
            scanf("%d%d%d", &s.x1, &s.y1, &s.radius);
            addObject(s);
            redraw();
            break;

        case 4:
            s.type = TRIANGLE;
            printf("Enter top-left point (x y): ");
            scanf("%d%d", &s.x1, &s.y1);

            printf("Enter base and height: ");
            scanf("%d%d", &s.base, &s.height);

            addObject(s);
            redraw();
            break;

        case 5:
            printf("Enter object index (0 to %d): ", objectCount - 1);
            scanf("%d", &index);
            deleteObject(index);
            redraw();
            break;

        case 6:
            printf("Enter object index to modify: ");
            scanf("%d", &index);

            if (index >= 0 && index < objectCount)
            {
                s = objects[index];

                if (s.type == LINE)
                {
                    printf("Enter new x1 y1 x2 y2: ");
                    scanf("%d%d%d%d", &s.x1, &s.y1, &s.x2, &s.y2);
                }
                else if (s.type == RECTANGLE)
                {
                    printf("Enter new x1 y1 x2 y2: ");
                    scanf("%d%d%d%d", &s.x1, &s.y1, &s.x2, &s.y2);
                }
                else if (s.type == CIRCLE)
                {
                    printf("Enter new center x y radius: ");
                    scanf("%d%d%d", &s.x1, &s.y1, &s.radius);
                }
                else if (s.type == TRIANGLE)
                {
                    printf("Enter new top-left point (x y): ");
                    scanf("%d%d", &s.x1, &s.y1);

                    printf("Enter new base and height: ");
                    scanf("%d%d", &s.base, &s.height);
                }

                modifyObject(index, s);
                redraw();
            }
            else
            {
                printf("Invalid object index!\n");
            }
            break;

        case 7:
            displayCanvas();
            break;

        case 8:
            printf("Exiting...\n");
            return 0;

        default:
            printf("Invalid choice!\n");
        }
    }

    return 0;
}