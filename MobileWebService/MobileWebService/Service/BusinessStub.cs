using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Data.SqlClient;
using MobileWebService.Validater;
using MobileWebService.Entity;
using System.Data;

namespace MobileWebService.Service
{
    public class BusinessStub
    {
        //获取售卡记录
        public static List<SellCardItem> GetSellCardRecordByCondition(int top, string condition, string tableName)
        {
            var list = new List<SellCardItem>();

            string topMessage = "";
            string selectCondition = "";
            if (top != 0) //查询头几条
            {
                topMessage = " TOP " + top;
            }
            else
            {
                topMessage = "";
            }

            if (!string.IsNullOrEmpty(condition))
            {
                selectCondition = "Where " + condition;
            }
            var selectCommand = string.Format("SELECT {0} * FROM [MobileManage].[dbo].{1} {2} ", topMessage, tableName, selectCondition);//组合选择语句
            using (SqlConnection con = DBConn.CreateConn())//新建数据库连接
            {
                try
                {
                    con.Open();

                    using (var cmd = new SqlCommand())
                    {
                        cmd.CommandText = selectCommand;
                        cmd.CommandType = CommandType.Text;
                        cmd.Connection = con;
                        using (SqlDataReader sdr = cmd.ExecuteReader())// cmd2.ExecuteNonQuery();
                        {
                            if (sdr.HasRows)
                            {
                                while (sdr.Read())
                                {
                                    var sellCardItem = new SellCardItem();
                                    if (!string.IsNullOrEmpty(sdr["Id"].ToString()))
                                        sellCardItem.Id = new Guid(sdr["Id"].ToString());
                                    if (!string.IsNullOrEmpty(sdr["销售用户ID"].ToString()))
                                        sellCardItem.user_id = new Guid(sdr["销售用户ID"].ToString());
                                    sellCardItem.user_name = sdr["网点用户登录名"].ToString();
                                    if (!string.IsNullOrEmpty(sdr["销售时间"].ToString()))
                                        sellCardItem.sellTime = Convert.ToDateTime(sdr["销售时间"].ToString());
                                    if (!string.IsNullOrEmpty(sdr["业务负责人Id"].ToString()))
                                        sellCardItem.manager_id = new Guid(sdr["业务负责人Id"].ToString());
                                    sellCardItem.manager_name = sdr["业务负责人"].ToString();
                                    if (!string.IsNullOrEmpty(sdr["员工Id"].ToString()))
                                        sellCardItem.work_id = new Guid(sdr["员工Id"].ToString());
                                    if (!string.IsNullOrEmpty(sdr["其他业务"].ToString()))
                                        sellCardItem.isOtherService = Convert.ToBoolean(sdr["其他业务"].ToString());
                                    sellCardItem.work_name = sdr["员工登录名"].ToString();
                                    sellCardItem.telNo = sdr["电话号码"].ToString();
                                    sellCardItem.miniNo = sdr["小卡号码"].ToString();
                                    sellCardItem.passwd = sdr["开卡服务密码"].ToString();
                                    sellCardItem.brand = sdr["套餐名称"].ToString();
                                    sellCardItem.brandNo = sdr["套餐编号"].ToString();
                                    sellCardItem.cardPrice = sdr["开卡面值"].ToString();
                                    if (!string.IsNullOrEmpty(sdr["扣款金额"].ToString()))
                                        sellCardItem.chargeMoney = Convert.ToDouble(sdr["扣款金额"].ToString());
                                    if (!string.IsNullOrEmpty(sdr["处理前余额"].ToString()))
                                        sellCardItem.moneyBefore = Convert.ToDouble(sdr["处理前余额"].ToString());
                                    if (!string.IsNullOrEmpty(sdr["处理后余额"].ToString()))
                                        sellCardItem.moneyAfter = Convert.ToDouble(sdr["处理后余额"].ToString());
                                    sellCardItem.state = sdr["处理状态"].ToString();
                                    sellCardItem.SP = sdr["运营商"].ToString();
                                    sellCardItem.clientType = sdr["客户端类型"].ToString();
                                    sellCardItem.noSection = sdr["号段"].ToString();
                                    if (!string.IsNullOrEmpty(sdr["选号费"].ToString()))
                                        sellCardItem.noPrice = Convert.ToDouble(sdr["选号费"].ToString());
                                    sellCardItem.area = sdr["分区"].ToString();
                                    list.Add(sellCardItem);
                                }

                                cmd.Dispose();
                                sdr.Close();
                            }
                        }
                    }
                }
                catch (Exception ex)
                {
                    throw new Exception(ex.Message);
                }
                finally
                {
                    con.Close();
                }
            }

            return list;
        }

        //获取业务办理
        public static List<BusinessItem> GetBusinessRecordByCondition(int top, string condition, string tableName)
        {
            var list = new List<BusinessItem>();

            string topMessage = "";
            string selectCondition = "";
            if (top != 0) //查询头几条
            {
                topMessage = " TOP " + top;
            }
            else
            {
                topMessage = "";
            }

            if (!string.IsNullOrEmpty(condition))
            {
                selectCondition = "Where " + condition;
            }
            var selectCommand = string.Format("SELECT {0} * FROM [MobileManage].[dbo].{1} {2} ", topMessage, tableName, selectCondition);//组合选择语句
            using (SqlConnection con = DBConn.CreateConn())//新建数据库连接
            {
                try
                {
                    con.Open();

                    using (var cmd = new SqlCommand())
                    {
                        cmd.CommandText = selectCommand;
                        cmd.CommandType = CommandType.Text;
                        cmd.Connection = con;
                        using (SqlDataReader sdr = cmd.ExecuteReader())// cmd2.ExecuteNonQuery();
                        {
                            if (sdr.HasRows)
                            {
                                while (sdr.Read())
                                {
                                    var businessItem = new BusinessItem();
                                    if (!string.IsNullOrEmpty(sdr["Id"].ToString()))
                                        businessItem.Id = new Guid(sdr["Id"].ToString());
                                    businessItem.businessName = sdr["业务名称"].ToString();
                                    businessItem.businessSpec = sdr["业务明细"].ToString();
                                    if (!string.IsNullOrEmpty(sdr["提交网点用户Id"].ToString()))
                                        businessItem.userId = new Guid(sdr["提交网点用户Id"].ToString());
                                    businessItem.userName = sdr["网点用户登录名"].ToString();
                                    businessItem.sp = sdr["运营商"].ToString();
                                    businessItem.no = sdr["电话号码"].ToString();
                                    businessItem.passwd = sdr["密码"].ToString();
                                    if (!string.IsNullOrEmpty(sdr["办理时间"].ToString()))
                                        businessItem.datetime = Convert.ToDateTime(sdr["办理时间"].ToString());
                                    businessItem.state = sdr["办理状态"].ToString();
                                    businessItem.content = sdr["备注"].ToString();
                                    businessItem.replay = sdr["回复"].ToString();
                                    if (!string.IsNullOrEmpty(sdr["员工Id"].ToString()))
                                        businessItem.workerId = new Guid(sdr["员工Id"].ToString());
                                    businessItem.workerName = sdr["用户名"].ToString();
                                    businessItem.clientType = sdr["客户端类型"].ToString();
                                    if (!string.IsNullOrEmpty(sdr["返款金额"].ToString()))
                                        businessItem.returnMoney = Convert.ToDouble(sdr["返款金额"].ToString());
                                    list.Add(businessItem);
                                }

                                cmd.Dispose();
                                sdr.Close();
                            }
                        }
                    }
                }
                catch (Exception ex)
                {
                    throw new Exception(ex.Message);
                }
                finally
                {
                    con.Close();
                }
            }

            return list;
        }

        //获取卡类销售记录
        public static List<SellOtherCardItem> GetSellOtherRecordByCondition(int top, string condition, string tableName)
        {
            var list = new List<SellOtherCardItem>();

            string topMessage = "";
            string selectCondition = "";
            if (top != 0) //查询头几条
            {
                topMessage = " TOP " + top;
            }
            else
            {
                topMessage = "";
            }

            if (!string.IsNullOrEmpty(condition))
            {
                selectCondition = "Where " + condition;
            }
            var selectCommand = string.Format("SELECT {0} * FROM [MobileManage].[dbo].{1} {2} ", topMessage, tableName, selectCondition);//组合选择语句
            using (SqlConnection con = DBConn.CreateConn())//新建数据库连接
            {
                try
                {
                    con.Open();

                    using (var cmd = new SqlCommand())
                    {
                        cmd.CommandText = selectCommand;
                        cmd.CommandType = CommandType.Text;
                        cmd.Connection = con;
                        using (SqlDataReader sdr = cmd.ExecuteReader())// cmd2.ExecuteNonQuery();
                        {
                            if (sdr.HasRows)
                            {
                                while (sdr.Read())
                                {
                                    var sellOtherCardItem = new SellOtherCardItem();
                                    if (!string.IsNullOrEmpty(sdr["Id"].ToString()))
                                        sellOtherCardItem.Id = new Guid(sdr["Id"].ToString());
                                    if (!string.IsNullOrEmpty(sdr["网点用户Id"].ToString()))
                                        sellOtherCardItem.userId = new Guid(sdr["网点用户Id"].ToString());
                                    sellOtherCardItem.userName = sdr["网点用户登录名"].ToString();
                                    if (!string.IsNullOrEmpty(sdr["购买时间"].ToString()))
                                        sellOtherCardItem.datetime = Convert.ToDateTime(sdr["购买时间"].ToString());
                                    sellOtherCardItem.cardType = sdr["卡类型"].ToString();
                                    sellOtherCardItem.cardName = sdr["卡名称"].ToString();
                                    sellOtherCardItem.cardSeq = sdr["序列号"].ToString();
                                    sellOtherCardItem.cardPsw = sdr["卡密"].ToString();
                                    sellOtherCardItem.state = sdr["状态"].ToString();
                                    if (!string.IsNullOrEmpty(sdr["员工Id"].ToString()))
                                        sellOtherCardItem.workerId = new Guid(sdr["员工Id"].ToString());
                                    sellOtherCardItem.workerName = sdr["员工登录名"].ToString();
                                    if (!string.IsNullOrEmpty(sdr["扣款金额"].ToString()))
                                        sellOtherCardItem.chargeMoney = Convert.ToDouble(sdr["扣款金额"].ToString());
                                    if (!string.IsNullOrEmpty(sdr["处理前余额"].ToString()))
                                        sellOtherCardItem.moneyBefore = Convert.ToDouble(sdr["处理前余额"].ToString());
                                    if (!string.IsNullOrEmpty(sdr["处理后余额"].ToString()))
                                        sellOtherCardItem.moneyAfter = Convert.ToDouble(sdr["处理后余额"].ToString());
                                    sellOtherCardItem.clientType = sdr["客户端类型"].ToString();
                                    list.Add(sellOtherCardItem);
                                }

                                cmd.Dispose();
                                sdr.Close();
                            }
                        }
                    }
                }
                catch (Exception ex)
                {
                    throw new Exception(ex.Message);
                }
                finally
                {
                    con.Close();
                }
            }

            return list;
        }
    }
}