// class Player
// {
// public:
//     bool canDoubleJump;
//     bool canDash;
//     const int moveSpd = 5;
//     int lastKeyPressed;
//     int dashingFrames = 0;
//     int currentMoveSpd = moveSpd;
//     bool dashing = false;

//     void move()
//     {
//         // sprint key
//         if (IsKeyDown(KEY_LEFT_CONTROL))
//         {
//             currentMoveSpd = 1.4 * moveSpd;
//         }
//         else
//         {
//             currentMoveSpd = moveSpd;
//         }

//         // dashing
//         if (IsKeyPressed(KEY_LEFT_SHIFT))
//         {
//             if (dashingFrames == 0)
//             {
//                 dashing = true;
//                 dashingFrames = 15;
//             }
//         }
//         else if (dashing)
//         {
//             double dashDistance = currentMoveSpd * (1 + dashingFrames / 5.0);
//             if (IsKeyDown(KEY_W))
//             {
//                 if (IsKeyDown(KEY_D))
//                 {
//                     ball_x += dashDistance / sqrt(2);
//                     ball_y -= dashDistance / sqrt(2);
//                     lastKeyPressed = 1;
//                 }
//                 else if (IsKeyDown(KEY_A))
//                 {
//                     ball_x -= dashDistance / sqrt(2);
//                     ball_y -= dashDistance / sqrt(2);
//                     lastKeyPressed = 2;
//                 }
//                 else if (!IsKeyDown(KEY_S))
//                 {
//                     ball_y -= dashDistance;
//                     lastKeyPressed = KEY_W;
//                 }
//             }
//             else if (IsKeyDown(KEY_S))
//             {
//                 if (IsKeyDown(KEY_D))
//                 {
//                     ball_x += dashDistance / sqrt(2);
//                     ball_y += dashDistance / sqrt(2);
//                     lastKeyPressed = 4;
//                 }
//                 else if (IsKeyDown(KEY_A))
//                 {
//                     ball_x -= dashDistance / sqrt(2);
//                     ball_y += dashDistance / sqrt(2);
//                     lastKeyPressed = 3;
//                 }
//                 else if (!IsKeyDown(KEY_W))
//                 {
//                     ball_y += dashDistance;
//                     lastKeyPressed = KEY_S;
//                 }
//             }
//             else if (IsKeyDown(KEY_D) && !IsKeyDown(KEY_A))
//             {
//                 ball_x += dashDistance;
//                 lastKeyPressed = KEY_D;
//             }
//             else if (IsKeyDown(KEY_A) && !IsKeyDown(KEY_D))
//             {
//                 ball_x -= dashDistance;
//                 lastKeyPressed = KEY_A;
//             }
//             else if (lastKeyPressed == KEY_W)
//             {
//                 ball_y -= dashDistance;
//             }
//             else if (lastKeyPressed == KEY_S)
//             {
//                 ball_y += dashDistance;
//             }
//             else if (lastKeyPressed == KEY_A)
//             {
//                 ball_x -= dashDistance;
//             }
//             else if (lastKeyPressed == KEY_D)
//             {
//                 ball_x += dashDistance;
//             }
//             else if (lastKeyPressed == 1) // 1 = NE, 2 = NW, 3 = SW, 4 = SE (quadrants)
//             {
//                 ball_x += dashDistance / sqrt(2);
//                 ball_y -= dashDistance / sqrt(2);
//             }
//             else if (lastKeyPressed == 2)
//             {
//                 ball_x -= dashDistance / sqrt(2);
//                 ball_y -= dashDistance / sqrt(2);
//             }
//             else if (lastKeyPressed == 3)
//             {
//                 ball_x -= dashDistance / sqrt(2);
//                 ball_y += dashDistance / sqrt(2);
//             }
//             else if (lastKeyPressed == 4)
//             {
//                 ball_x += dashDistance / sqrt(2);
//                 ball_y += dashDistance / sqrt(2);
//             }
//             dashingFrames--;
//             cout << "dashingFrames = " << dashingFrames << "\ndashDistance = " << dashDistance << endl;
//             if (dashingFrames == 0)
//             {
//                 dashing = false;
//             }
//         }
//         else if (IsKeyDown(KEY_W)) // basic WASD movement
//         {
//             if (IsKeyDown(KEY_D))
//             {
//                 ball_x += currentMoveSpd / sqrt(2);
//                 ball_y -= currentMoveSpd / sqrt(2);
//             }
//             else if (IsKeyDown(KEY_A))
//             {
//                 ball_x -= currentMoveSpd / sqrt(2);
//                 ball_y -= currentMoveSpd / sqrt(2);
//             }
//             else if (!IsKeyDown(KEY_S))
//             {
//                 ball_y -= currentMoveSpd;
//             }
//         }
//         else if (IsKeyDown(KEY_S))
//         {
//             if (IsKeyDown(KEY_D))
//             {
//                 ball_x += currentMoveSpd / sqrt(2);
//                 ball_y += currentMoveSpd / sqrt(2);
//             }
//             else if (IsKeyDown(KEY_A))
//             {
//                 ball_x -= currentMoveSpd / sqrt(2);
//                 ball_y += currentMoveSpd / sqrt(2);
//             }
//             else if (!IsKeyDown(KEY_W))
//             {
//                 ball_y += currentMoveSpd;
//             }
//         }
//         else if (IsKeyDown(KEY_D) && !IsKeyDown(KEY_A))
//         {
//             ball_x += currentMoveSpd;
//         }
//         else if (IsKeyDown(KEY_A) && !IsKeyDown(KEY_D))
//         {
//             ball_x -= currentMoveSpd;
//         }
//     }
// };