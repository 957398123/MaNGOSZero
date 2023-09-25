/**
 * MaNGOS is a full featured server for World of Warcraft, supporting
 * the following clients: 1.12.x, 2.4.3, 3.3.5a, 4.3.4a and 5.4.8
 *
 * Copyright (C) 2005-2023 MaNGOS <https://getmangos.eu>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 * World of Warcraft, and all World of Warcraft or Warcraft art, images,
 * and lore are copyrighted by Blizzard Entertainment, Inc.
 */

#ifndef MANGOS_H_EVENTPROCESSOR
#define MANGOS_H_EVENTPROCESSOR

#include "Platform/Define.h"

#include <map>

/**
 * @brief ����ʱ�䵥λΪ����
 *
 */
class BasicEvent
{
    public:

        /**
         * @brief
         *
         */
        BasicEvent()
            : to_Abort(false)
        {
        }

        /**
         * @brief override destructor to perform some actions on event removal
         *
         */
        virtual ~BasicEvent()
        {
        };


        /**
         * @brief ���������Event��������ʱ��ִ��
         *
         * @param uint64 e_time ��ʼִ��ʱ��
         * @param uint32 p_time ���¼��
         * @return bool �������Ҫɾ��Event������false
         */
        virtual bool Execute(uint64 /*e_time*/, uint32 /*p_time*/) { return true; }

        /**
         * @brief Event�ܷ񱻰�ȫ��ɾ��
         *
         * @return bool
         */
        virtual bool IsDeletable() const { return true; }

        /**
         * @brief ���������Event��ֹʱִ��
         *
         * @param uint64
         */
        virtual void Abort(uint64 /*e_time*/) {}

        /**
         * @brief �Ƿ���ֹEvent����ֹʱ����Abort����
        */
        bool to_Abort;

        /**
         * @brief Event���봦����е�ʱ��
        */
        uint64 m_addTime;
        /**
         * @brief Event����ʱ��
        */
        uint64 m_execTime;
};

/**
 * @brief
 *
 */
typedef std::multimap<uint64, BasicEvent*> EventList;

/**
 * @brief
 *
 */
class EventProcessor
{
    public:

        /**
         * @brief
         *
         */
        EventProcessor();
        /**
         * @brief
         *
         */
        ~EventProcessor();

        /**
         * @brief ����EventProcessor��ʱ��
         * @param p_time ���ӵ�ʱ�� 
        */
        void Update(uint32 p_time); 
        /**
         * @brief �ر������¼�
         * @param �Ƿ�ǿ�ƹر�
        */
        void KillAllEvents(bool force);
        /**
         * @brief ���Event���������
         * @param Event Ҫ�����Event
         * @param e_time Event����ʱ��
         * @param set_addtime �Ƿ�����Event����ʱ��
        */
        void AddEvent(BasicEvent* Event, uint64 e_time, bool set_addtime = true);
        /**
         * @brief ����ʱ��
         * @param t_offset Ҫ���ӵ�ʱ��
         * @return ��ǰʱ��+���ӵ�ʱ��
        */
        uint64 CalculateTime(uint64 t_offset);

    protected:

        /**
         * @brief ��ǰʱ��
        */
        uint64 m_time;
        /**
         * @brief Event�������
        */
        EventList m_events;
        /**
         * @brief �Ƿ���ֹEvent����
        */
        bool m_aborting;
};

#endif
