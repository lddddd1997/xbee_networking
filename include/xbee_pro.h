/**
 * @file    xbee_pro.h
 * @author  lddddd
 * @brief   xbee pro s2c组网通信
 * @details
 * @note
 * @date    2020.6.11
 * @version 1.0
 */
#ifndef COMMUNICATION_XBEE_PRO_H_
#define COMMUNICATION_XBEE_PRO_H_

#include "serial_port.h"
namespace lddddd
{
struct CommunicationData         //机间数据
{
    int uav_id_;                 //无人机ID

    int task_target_id_;         //目标编号
    int task_flag_;              //标志位（0为编队或搜索，1为执行任务）
    int task_type_;              //任务类型

    float pos_uav_[3];           //无人机位置信息 x y z
    float yaw_uav_;              //无人机偏航

    int target_id_;              //目标ID
    float pos_target_[3];        //目标信息 x y v 
    float yaw_target_;           //目标偏航
    int num_;                    //车身数字
    int num_side_;               //数字在哪一侧
    int target_find_;            //发现目标标志
    int target_find_uav_id_;     //发现者
    int num_change_;             //数字改变

    int assign_array_[9];        //分配情况（3*3矩阵，每个目标分配的无人机情况）
};

// struct FrameSend         //Xbee数传数据
// {                                        //default
//     unsigned char start_delimiter_;      //7E
//     unsigned char length_[2];            //00 1A     ***
//     unsigned char frame_type_;           //11
//     unsigned char frame_id_;             //00
//     unsigned char dest_address_64_[8];   //00 13 A2 00 41 5A B7 68      ***
//     unsigned char dest_address_16_[2];   //FF FE
//     unsigned char source_endpoint_;      //E8
//     unsigned char destination_endpoint_; //E8
//     unsigned char cluster_id_[2];        //00 11
//     unsigned char profile_id_[2];        //C1 05
//     unsigned char broadcast_radius_;     //00
//     unsigned char options_;              //00
//     unsigned char data_payload_[100];    //41 42 43 44 45 46   ***
//     unsigned char check_sum_;            //46       ***
// };

// struct FrameRead
// {                                        //default
//     unsigned char start_delimiter_;      //7E
//     unsigned char length_[2];            //00 18
//     unsigned char frame_type_;           //91
//     unsigned char dest_address_64_[8];   //00 13 A2 00 41 5A B7 68
//     unsigned char dest_address_16_[2];   //FF FE
//     unsigned char source_endpoint_;      //E8
//     unsigned char destination_endpoint_; //E8
//     unsigned char cluster_id_[2];        //00 11
//     unsigned char profile_id_[2];        //C1 05
//     unsigned char receive_options_;      //00
//     unsigned char receive_data_[100];    //41 42 43 44 45 46
//     unsigned char check_sum_;            //C6 
// };

class XbeePro : public lddddd::Serial
{
public:
    enum Mode
    {
        RDWR = 0u,
        O_RD = 1u,
        O_WR = 2u
    };

    XbeePro(const std::string _name, const int _baud_rate, Mode _mode, const ros::NodeHandle& _nh);
    ~XbeePro();
    void TaskRun(void);
    friend std::ostream& operator<<(std::ostream& _out, const CommunicationData& _data);

private:
    ros::NodeHandle nh_;
    ros::Timer loop_timer_;
    const unsigned char xbee_address_[5][8];

    void (*FunctionPointer_)(void);    
    void CyclicRead(void);
    void CyclicSpin(void);

    void LoopTimerCallback(const ros::TimerEvent& _event);
    void XbeeFrameWrite(const CommunicationData* _data, const int _uav_dest_id);
    void XbeeFrameRead(CommunicationData* _data);
};

std::ostream& operator<<(std::ostream& _out, const CommunicationData& _data)
{
    ROS_INFO("~~~~~~~~~~~~~~~~~~~~~~~~Reception~~~~~~~~~~~~~~~~~~~~~~~~\n");
    _out << "uav_id_:  " << _data.uav_id_ << std::endl;
    _out << "task_target_id_:  " << _data.task_target_id_ << std::endl;
    _out << "task_flag_:  " << _data.task_flag_ << std::endl;
    _out << "task_type_:  " << _data.task_type_ << std::endl;
    _out << "pos_uav_x_:  " << _data.pos_uav_[0] << std::endl;
    _out << "pos_uav_y_:  " << _data.pos_uav_[1] << std::endl;
    _out << "pos_uav_z_:  " << _data.pos_uav_[2] << std::endl;
    _out << "yaw_uav_:  " << _data.yaw_uav_ << std::endl;
    _out << "target_id_:  " << _data.target_id_ << std::endl;
    _out << "pos_target_x_:  " << _data.pos_target_[0] << std::endl;
    _out << "pos_target_y_:  " << _data.pos_target_[1] << std::endl;
    _out << "pos_target_z_:  " << _data.pos_target_[2] << std::endl;
    _out << "yaw_target_:  " << _data.yaw_target_ << std::endl;
    _out << "num_:  " << _data.num_ << std::endl;
    _out << "num_side_:  " << _data.num_side_ << std::endl;
    _out << "target_find_:  " << _data.target_find_ << std::endl;
    _out << "target_find_uav_id_:  " << _data.target_find_uav_id_ << std::endl;
    _out << "num_change_:  " << _data.num_change_ << std::endl;
    _out << "assign_array_[0]:  " << _data.assign_array_[0] << std::endl;
    _out << "assign_array_[1]:  " << _data.assign_array_[1] << std::endl;
    _out << "assign_array_[2]:  " << _data.assign_array_[2] << std::endl;
    _out << "assign_array_[3]:  " << _data.assign_array_[3] << std::endl;
    _out << "assign_array_[4]:  " << _data.assign_array_[4] << std::endl;
    _out << "assign_array_[5]:  " << _data.assign_array_[5] << std::endl;
    _out << "assign_array_[6]:  " << _data.assign_array_[6] << std::endl;
    _out << "assign_array_[7]:  " << _data.assign_array_[7] << std::endl;
    _out << "assign_array_[8]:  " << _data.assign_array_[8] << std::endl;
}

void XbeePro::LoopTimerCallback(const ros::TimerEvent& _event)
{
    CommunicationData UavData;
    UavData.uav_id_ = 0;
    UavData.task_target_id_ = 2;
    UavData.task_flag_ = 1;
    UavData.task_type_ = 1;
    UavData.pos_uav_[0] = 11.1;
    UavData.pos_uav_[1] = 22.2;
    UavData.pos_uav_[2] = 33.3;
    UavData.yaw_uav_ = 3.14;
    UavData.target_id_ = 2;
    UavData.pos_target_[0] = 44.4;
    UavData.pos_target_[1] = 55.5;
    UavData.pos_target_[2] = 66.6;
    UavData.yaw_target_ = 1.57;
    UavData.num_ = 2;
    UavData.num_side_ = 1;
    UavData.target_find_ = 1;
    UavData.target_find_uav_id_ = 2;
    UavData.num_change_ = 1;
    UavData.assign_array_[0] = 0;
    UavData.assign_array_[1] = 1;
    UavData.assign_array_[2] = 2;
    UavData.assign_array_[3] = 3;
    UavData.assign_array_[4] = 4;
    UavData.assign_array_[5] = 3;
    UavData.assign_array_[6] = 2;
    UavData.assign_array_[7] = 1;
    UavData.assign_array_[8] = 0;
    // XbeeFrameWrite(&UavData, 1);    //往3号无人机发送
    // XbeeFrameWrite(&UavData, 2);    //往3号无人机发送
    XbeeFrameWrite(&UavData, 3);    //往3号无人机发送

}

void XbeePro::CyclicRead(void)
{
    lddddd::CommunicationData CooperationData;

    XbeeFrameRead(&CooperationData);
}

void XbeePro::CyclicSpin(void)
{
    ros::spin();
}

void XbeePro::TaskRun(void)
{
    // (*FunctionPoint_)();
    FunctionPointer_();
}

void XbeePro::XbeeFrameWrite(const CommunicationData* _data, const int _uav_dest_id)
{
    unsigned char data_buf[100] = {0};
    int frame_length = 58;//固定长度frame_length~check_sum
    data_buf[0] = 0x7E;
    
    data_buf[1] = 0x00;
    data_buf[2] = (unsigned char)frame_length;

    data_buf[3] = 0x11;
    data_buf[4] = 0x00;

    memcpy(&data_buf[5], xbee_address_[_uav_dest_id], 8);

    data_buf[13] = 0xFF;
    data_buf[14] = 0xFE;
    data_buf[15] = 0xE8;
    data_buf[16] = 0xE8;
    data_buf[17] = 0x00;
    data_buf[18] = 0x11;
    data_buf[19] = 0xC1;
    data_buf[20] = 0x05;
    data_buf[21] = 0x00;
    data_buf[22] = 0x00;

    //23~end data_payload
    data_buf[23] = ((_data->uav_id_ & 0x07) << 5) | ((_data->task_target_id_ & 0x03) << 3) 
                | ((_data->task_flag_ & 0x01) << 2) | (_data->task_type_ & 0x03);//7 6 5（存放uav_id） 4 3 （存放task_target_id） 2 （存放task_flag） 1 0 （存放task_type）
    memcpy(&data_buf[24], (unsigned char*)&_data->pos_uav_[0], 4);//24~27
    memcpy(&data_buf[28], (unsigned char*)&_data->pos_uav_[1], 4);//28~31
    memcpy(&data_buf[32], (unsigned char*)&_data->pos_uav_[2], 4);//32~35
    memcpy(&data_buf[36], (unsigned char*)&_data->yaw_uav_, 4);   //36~39

    data_buf[40] = ((_data->target_id_ & 0x03) << 6) | ((_data->num_ & 0x03) << 4)
                | ((_data->num_side_ & 0x01) << 3) | (_data->target_find_uav_id_ & 0x07);//7 6 （存放target_id） 5 4 （存放num） 3 （存放num_side） 2 1 0 （存放target_find_uav_id）

    memcpy(&data_buf[41], (unsigned char*)&_data->pos_target_[0], 4);//41~44
    memcpy(&data_buf[45], (unsigned char*)&_data->pos_target_[1], 4);//45~48
    memcpy(&data_buf[49], (unsigned char*)&_data->pos_target_[2], 4);//49~52
    memcpy(&data_buf[53], (unsigned char*)&_data->yaw_target_, 4);   //53~56

    data_buf[57] = ((_data->target_find_ & 0x01) << 7) | ((_data->num_change_ & 0x01) << 6)//7 （存放target_find） 6 （存放num_change） 5 4 3 （assign_array[0]） 2 1 0 （assign_array[1]）
                | ((_data->assign_array_[0] & 0x07) << 3) | (_data->assign_array_[1] & 0x07);
    data_buf[58] = ((_data->assign_array_[2] & 0x07) << 3) | (_data->assign_array_[3] & 0x07);
    data_buf[59] = ((_data->assign_array_[8] & 0x06) << 6) | ((_data->assign_array_[4] & 0x07) << 3) //assign_array_[8]分散存储
                | (_data->assign_array_[5] & 0x07);
    data_buf[60] = ((_data->assign_array_[8] & 0x01) << 7) | ((_data->assign_array_[6] & 0x07) << 3) 
                | (_data->assign_array_[7] & 0x07);

    unsigned char* begin = &data_buf[3];
    data_buf[61] = 0xFF - (std::accumulate(begin, begin + frame_length, 0x00) & 0xFF);  //check_sum

    if(DataWrite(data_buf, frame_length + 4))
    {
        // ROS_INFO("Data Send Succesed!");
    }
    else
    {
        ROS_ERROR_STREAM("Data Send Error!");
    }
}

void XbeePro::XbeeFrameRead(CommunicationData* _data)
{
    unsigned char data_buf[100] = {0};
    int frame_length;
    static double read_time;
    while(true)
    {
        if(DataRead(data_buf, 1))
        {
            if(data_buf[0] == 0x7E)
            {
                // fcntl(serial_, F_SETFL, 0);    //设置为阻塞
                if(DataRead(data_buf, 3))
                {
                    if(data_buf[0] == 0x00 && data_buf[2] == 0x91)
                    {
                        frame_length = data_buf[1];
                        break;
                    }
                }
                else
                {
                    ROS_ERROR_STREAM("Data Read Error Timeout 3 !");
                    return ;
                }
            }
            else
            {
                ROS_ERROR_STREAM("Data Read Error Head !");
                return ;
                // fcntl(serial_, F_SETFL, FNDELAY);    //设置为非阻塞
            }
        }
        else
        {
            ROS_ERROR_STREAM("Data Read Error Timeout 1 !");
            return ;
        }
    }
    memset(data_buf, 0, 100);
    if(DataRead(data_buf, frame_length))    //4~end
    {
        unsigned char sum_check = std::accumulate(data_buf, data_buf + frame_length, 0x91) & 0xFF;    //The accumulation from 3 to end is equal to 0xFF
        if(sum_check == 0xFF)
        {
            _data->uav_id_ = (data_buf[17] & (unsigned char)(0x07 << 5)) >> 5;    //17~end receive_data
            _data->task_target_id_ = (data_buf[17] & (unsigned char)(0x03 << 3)) >> 3;
            _data->task_flag_ = (data_buf[17] & (unsigned char)(0x01 << 2)) >> 2;
            _data->task_type_ = (data_buf[17] & (unsigned char)0x03);

            memcpy((unsigned char*)&_data->pos_uav_[0], &data_buf[18], 4);
            memcpy((unsigned char*)&_data->pos_uav_[1], &data_buf[22], 4);
            memcpy((unsigned char*)&_data->pos_uav_[2], &data_buf[26], 4);
            memcpy((unsigned char*)&_data->yaw_uav_, &data_buf[30], 4);

            _data->target_id_ = (data_buf[34] & (unsigned char)(0x03 << 6)) >> 6;
            _data->num_ = (data_buf[34] & (unsigned char)(0x03 << 4)) >> 4;
            _data->num_side_ = (data_buf[34] & (unsigned char)(0x01 << 3)) >> 3;
            _data->target_find_uav_id_ = (data_buf[34] & (unsigned char)0x07);

            memcpy((unsigned char*)&_data->pos_target_[0], &data_buf[35], 4);
            memcpy((unsigned char*)&_data->pos_target_[1], &data_buf[39], 4);
            memcpy((unsigned char*)&_data->pos_target_[2], &data_buf[43], 4);
            memcpy((unsigned char*)&_data->yaw_target_, &data_buf[47], 4);

            _data->target_find_ = (data_buf[51] & (unsigned char)(0x01 << 7)) >> 7;
            _data->num_change_ = (data_buf[51] & (unsigned char)(0x01 << 6)) >> 6;
            _data->assign_array_[0] = (data_buf[51] & (unsigned char)(0x07 << 3)) >> 3;
            _data->assign_array_[1] = (data_buf[51] & (unsigned char)0x07);

            _data->assign_array_[2] = (data_buf[52] & (unsigned char)(0x07 << 3)) >> 3;
            _data->assign_array_[3] = (data_buf[52] & (unsigned char)0x07);

            _data->assign_array_[4] = (data_buf[53] & (unsigned char)(0x07 << 3)) >> 3;
            _data->assign_array_[5] = (data_buf[53] & (unsigned char)0x07);

            _data->assign_array_[6] = (data_buf[54] & (unsigned char)(0x07 << 3)) >> 3;
            _data->assign_array_[7] = (data_buf[54] & (unsigned char)0x07);

            _data->assign_array_[8] = ((data_buf[53] & (unsigned char)(0x06 << 6)) >> 6) | ((data_buf[54] & (unsigned char)(0x01 << 7)) >> 7);

            std::cout << *_data << std::endl;
            // PrintCommunicationData(_data);

            std::cout << "read period: " <<  ros::Time().now().sec + ros::Time().now().nsec / 1e9 - read_time << " [s]" << std::endl;

            read_time = ros::Time().now().sec + ros::Time().now().nsec / 1e9;

            // fcntl(serial_, F_SETFL, FNDELAY);    //设置为非阻塞
        }
        else
        {
            // fcntl(serial_, F_SETFL, FNDELAY);    //设置为非阻塞
            ROS_ERROR_STREAM("Data Read Error In Data Read Sum Check !");
        }
    }
    else
    {
        ROS_ERROR_STREAM("Data Read Error Timeout Frame Length !");
    }
}

XbeePro::XbeePro(const std::string _name, const int _baud_rate, Mode _mode, const ros::NodeHandle& _nh) : Serial(_name, _baud_rate), nh_(_nh),
                                                                                                        xbee_address_
                                                                                                        {
                                                                                                            {0x00, 0x13, 0xA2, 0x00, 0x41, 0x5A, 0xB7, 0x62},//   0
                                                                                                            {0x00, 0x13, 0xA2, 0x00, 0x41, 0x5A, 0xB7, 0x68},//   1
                                                                                                            {0x00, 0x13, 0xA2, 0x00, 0x41, 0x5A, 0xB7, 0x6A},//   2
                                                                                                            {0x00, 0x13, 0xA2, 0x00, 0x41, 0x5A, 0xB7, 0x77},//   3
                                                                                                            {0x00, 0x13, 0xA2, 0x00, 0x41, 0x5A, 0xB7, 0x68} //   4
                                                                                                        }
{
    double period;
    nh_.param("/read_period", period, 0.08);
    // loop_timer_ = nh_.createTimer(ros::Duration(period), &lddddd::XbeePro::LoopTimerCallback, this);

    switch(_mode)
    {
        case(RDWR):
        {
            FunctionPointer_ = &lddddd::XbeePro::CyclicRead;
            loop_timer_ = nh_.createTimer(ros::Duration(period), &lddddd::XbeePro::LoopTimerCallback, this);
            break;
        }
        case(O_RD):
        {
            FunctionPointer_ = &CyclicRead;
            break;
        }
        case(O_WR):
        {
            FunctionPointer_ = &CyclicSpin;
            loop_timer_ = nh_.createTimer(ros::Duration(period), &lddddd::XbeePro::LoopTimerCallback, this);
            break;
        }
        default:
        {

            break;
        }
    }
}

XbeePro::~XbeePro()
{
    ClosePort();
}

}

#endif

      

