//
// Created by LEI XU on 4/27/19.
//

#ifndef RASTERIZER_TEXTURE_H
#define RASTERIZER_TEXTURE_H
#include "global.hpp"
#include <eigen3/Eigen/Eigen>
#include <opencv2/opencv.hpp>
class Texture{
private:
    cv::Mat image_data;

public:
    Texture(const std::string& name)
    {
        image_data = cv::imread(name);
        cv::cvtColor(image_data, image_data, cv::COLOR_RGB2BGR);
        width = image_data.cols;
        height = image_data.rows;
    }

    int width, height;

    Eigen::Vector3f getColor(float u, float v)
    {
        auto u_img = u * width;
        auto v_img = (1 - v) * height;
        auto color = image_data.at<cv::Vec3b>(v_img, u_img);
        return Eigen::Vector3f(color[0], color[1], color[2]);
    }

    Eigen::Vector3f getColorBilinear(float u, float v)
    {
        auto u_point = std::clamp(u * width, 0.f, (float)width);
        auto v_point = std::clamp((1 - v) * height, 0.f, float(height));

        auto u_left = std::clamp(std::floor(u_point), 0.f, (float)width);
        auto u_right = std::clamp(std::ceil(u_point), 0.f, (float)width);
        auto v_bottom = std::clamp(std::floor(v_point), 0.f, (float)height);
        auto v_top = std::clamp(std::ceil(v_point), 0.f, float(height));

        auto alpha = u_point - u_left;
        auto beta = v_point - v_bottom;

        auto col_lb = image_data.at<cv::Vec3b>(v_bottom, u_left);
        auto col_rb = image_data.at<cv::Vec3b>(v_bottom, u_right);
        auto col_lt = image_data.at<cv::Vec3b>(v_top, u_left);
        auto col_rt = image_data.at<cv::Vec3b>(v_top, u_right);
        
        auto color_b = col_lb + alpha * (col_rb - col_lb);
        auto color_t = col_lt + alpha * (col_rt - col_lt);
        auto color = color_b + beta * (color_t - color_b);
        return Eigen::Vector3f(color[0], color[1], color[2]);
    }

};
#endif //RASTERIZER_TEXTURE_H
